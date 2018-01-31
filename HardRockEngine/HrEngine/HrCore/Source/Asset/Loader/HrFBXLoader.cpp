#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "fbxsdk.h"

using namespace Hr;

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(->GetIOSettings()))
#endif

HrFBXLoader::HrFBXLoader()
{
	m_pFbxManager = nullptr;
}

HrFBXLoader::~HrFBXLoader()
{
	
}

void HrFBXLoader::Load(std::string& strFile, HrModelDescInfo& modelDesc)
{
	FbxString fbxFilePath(strFile.c_str());

	InitializeSDKObjects();
	if (LoadScene(fbxFilePath.Buffer()))
	{
		ParseFBXSdkScene(modelDesc);
	}

	DestroySdkObjects( true);
}

void HrFBXLoader::InitializeSDKObjects()
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	m_pFbxManager = FbxManager::Create();
	if (!m_pFbxManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", m_pFbxManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	//FbxString lPath = FbxGetApplicationDirectory();
	//pManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	m_pScene = FbxScene::Create(m_pFbxManager, "My Scene");
	if (!m_pScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}

}

bool HrFBXLoader::LoadScene(const char* pFilename)
{
	int lFileMajor, lFileMinor, lFileRevision;
	int lSDKMajor, lSDKMinor, lSDKRevision;
	//int lFileFormat = -1;
	int i, lAnimStackCount;
	bool lStatus;
	char lPassword[1024];

	// Get the file version number generate by the FBX SDK.
	FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

	// Create an importer.
	FbxImporter* lImporter = FbxImporter::Create(m_pFbxManager, "");

	// Initialize the importer by providing a filename.
	const bool lImportStatus = lImporter->Initialize(pFilename, -1, m_pFbxManager->GetIOSettings());
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

	if (!lImportStatus)
	{
		FbxString error = lImporter->GetStatus().GetErrorString();
		FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
		FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

		if (lImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::eInvalidFileVersion)
		{
			FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
			FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
		}

		return false;
	}

	FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

	if (lImporter->IsFBX())
	{
		FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

		// From this point, it is possible to access animation stack information without
		// the expense of loading the entire file.

		FBXSDK_printf("Animation Stack Information\n");

		lAnimStackCount = lImporter->GetAnimStackCount();

		FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
		FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
		FBXSDK_printf("\n");

		for (i = 0; i < lAnimStackCount; i++)
		{
			FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

			FBXSDK_printf("    Animation Stack %d\n", i);
			FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			// Change the value of the import name if the animation stack should be imported 
			// under a different name.
			FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			// Set the value of the import state to false if the animation stack should be not
			// be imported. 
			FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			FBXSDK_printf("\n");
		}

		// Set the import states. By default, the import states are always set to 
		// true. The code below shows how to change these states.
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_MATERIAL, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_TEXTURE, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_LINK, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_SHAPE, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_GOBO, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_ANIMATION, true);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	// Import the scene.
	lStatus = lImporter->Import(m_pScene);

	if (lStatus == false && lImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::ePasswordError)
	{
		FBXSDK_printf("Please enter password: ");

		lPassword[0] = '\0';

		FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
			scanf("%s", lPassword);
		FBXSDK_CRT_SECURE_NO_WARNING_END

			FbxString lString(lPassword);

		m_pFbxManager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD, lString);
		m_pFbxManager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

		lStatus = lImporter->Import(m_pScene);

		if (lStatus == false && lImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::ePasswordError)
		{
			FBXSDK_printf("\nPassword is wrong, import aborted.\n");
		}
	}

	// Destroy the importer.
	lImporter->Destroy();

	return lStatus;
}

void HrFBXLoader::DestroySdkObjects(bool pExitStatus)
{
	//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
	if (m_pFbxManager) m_pFbxManager->Destroy();
	if (pExitStatus) FBXSDK_printf("Program Success!\n");
}

void HrFBXLoader::ParseFBXSdkScene( HrModelDescInfo& modelDesc)
{
	FbxGeometryConverter converter(m_pFbxManager);
	if (!converter.SplitMeshesPerMaterial(m_pScene, true))
	{
		FBXSDK_printf("ParseFBXSdkScene SplitMeshesPerMaterial failed!");
		return;
	}

	FbxNode* pNode = m_pScene->GetRootNode();
	if (pNode)
	{
		ParseFBXSdkNode(pNode, modelDesc);
	}
}

void HrFBXLoader::ParseFBXSdkNode(FbxNode* pNode, HrModelDescInfo& modelDesc)
{
	if (pNode->GetNodeAttribute() == nullptr)
	{
		//error
	}
	else
	{
		FbxNodeAttribute::EType attributeType = pNode->GetNodeAttribute()->GetAttributeType();
		switch (attributeType)
		{
		case FbxNodeAttribute::eMarker:
			break;
		case FbxNodeAttribute::eSkeleton:
			break;
		case FbxNodeAttribute::eMesh:
			ReadMesh(pNode, modelDesc);
			break;
		case FbxNodeAttribute::eNurbs:
			break;
		case FbxNodeAttribute::ePatch:
			break;
		case FbxNodeAttribute::eCamera:
			break;
		case FbxNodeAttribute::eLight:
			break;
		case FbxNodeAttribute::eLODGroup:
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < pNode->GetChildCount(); ++i)
	{
		ParseFBXSdkNode(pNode->GetChild(i), modelDesc);
	}
}

void HrFBXLoader::ReadMaterial(fbxsdk::FbxNode* pNode, HrModelDescInfo::HrSubMeshInfo& meshInfo)
{
	int nMaterialCount = pNode->GetMaterialCount();
	if (nMaterialCount > 0)
	{
		FbxPropertyT<FbxDouble3> lKFbxDouble3;
		FbxPropertyT<FbxDouble> lKFbxDouble1;
		FbxColor theColor;

		for (int nMaterialIndex = 0; nMaterialIndex < nMaterialCount; ++nMaterialIndex)
		{
			HrModelDescInfo::HrMaterialInfo& materialInfo = meshInfo.materialInfo;

			fbxsdk::FbxSurfaceMaterial* pSurfaceMaterial = pNode->GetMaterial(nMaterialIndex);
			materialInfo.strMaterialName = pSurfaceMaterial->GetName();

			if (pSurfaceMaterial->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
			{
				// Ambient Color
				lKFbxDouble3 = ((FbxSurfacePhong*)pSurfaceMaterial)->Ambient;
				materialInfo.v4Ambient.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Ambient.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Ambient.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Ambient.w() = 1.0f;

				// Diffuse Color
				lKFbxDouble3 = ((FbxSurfacePhong*)pSurfaceMaterial)->Diffuse;
				materialInfo.v4Diffuse.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Diffuse.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Diffuse.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Diffuse.w() = 1.0f;

				// Specular Color
				lKFbxDouble3 = ((FbxSurfacePhong*)pSurfaceMaterial)->Specular;
				materialInfo.v4Specular.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Specular.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Specular.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Specular.w() = 1.0f;

				// Emissive Color
				lKFbxDouble3 = ((FbxSurfacePhong*)pSurfaceMaterial)->Emissive;
				materialInfo.v4Emissive.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Emissive.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Emissive.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Emissive.w() = 1.0f;

				// Opacity
				lKFbxDouble1 = ((FbxSurfacePhong*)pSurfaceMaterial)->TransparencyFactor;
				materialInfo.fOpacity = lKFbxDouble1.Get();

				// Shininess
				lKFbxDouble1 = ((FbxSurfacePhong*)pSurfaceMaterial)->Shininess;
				materialInfo.fShininess = lKFbxDouble1.Get();

				// Reflectivity
				lKFbxDouble1 = ((FbxSurfacePhong*)pSurfaceMaterial)->ReflectionFactor;
				materialInfo.fReflectivity = lKFbxDouble1.Get();

			}
			else if (pSurfaceMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				// Ambient Color
				lKFbxDouble3 = ((FbxSurfaceLambert*)pSurfaceMaterial)->Ambient;
				materialInfo.v4Ambient.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Ambient.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Ambient.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Ambient.w() = 1.0f;

				// Diffuse Color
				lKFbxDouble3 = ((FbxSurfaceLambert*)pSurfaceMaterial)->Diffuse;
				materialInfo.v4Diffuse.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Diffuse.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Diffuse.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Diffuse.w() = 1.0f;

				// Emissive Color
				lKFbxDouble3 = ((FbxSurfaceLambert*)pSurfaceMaterial)->Emissive;
				materialInfo.v4Emissive.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Emissive.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Emissive.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Emissive.w() = 1.0f;

				// Opacity
				lKFbxDouble1 = ((FbxSurfaceLambert*)pSurfaceMaterial)->TransparencyFactor;
				materialInfo.fOpacity = lKFbxDouble1.Get();

			}

			//FbxProperty property;
			if (pSurfaceMaterial)
			{
				for (int nTextureIndex = 0; nTextureIndex < FbxLayerElement::sTypeTextureCount; ++nTextureIndex)
				{
					FbxProperty property = pSurfaceMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[nTextureIndex]);
					if (property.IsValid())
					{
						//Here we have to check if it's layered textures, or just textures:
						int32 LayeredTextureCount = property.GetSrcObjectCount<FbxLayeredTexture>();
						FbxString PropertyName = property.GetName();
						if (LayeredTextureCount > 0)
						{
							//for (int32 LayerIndex = 0; LayerIndex < LayeredTextureCount; ++LayerIndex)
							//{
							//	FbxLayeredTexture *lLayeredTexture = property.GetSrcObject<FbxLayeredTexture>(LayerIndex);
							//	int32 NbTextures = lLayeredTexture->GetSrcObjectCount<FbxTexture>();
							//	for (int32 TexIndex = 0; TexIndex < NbTextures; ++TexIndex)
							//	{
							//		FbxFileTexture* Texture = lLayeredTexture->GetSrcObject<FbxFileTexture>(TexIndex);
							//	}
							//}
						}
						else
						{
							//no layered texture simply get on the property
							int32 NbTextures = property.GetSrcObjectCount<FbxTexture>();
							for (int32 TexIndex = 0; TexIndex < NbTextures; ++TexIndex)
							{

								FbxFileTexture* Texture = property.GetSrcObject<FbxFileTexture>(TexIndex);
								if (Texture)
								{
									std::string Filename1 = Texture->GetFileName();
									if (std::find_if(meshInfo.vecTextureFileName.begin(), meshInfo.vecTextureFileName.end(), [&](std::string& item) {return (item == Filename1); }) == meshInfo.vecTextureFileName.end())
									{
										meshInfo.vecTextureFileName.push_back(Filename1);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void HrFBXLoader::ReadMesh(FbxNode* pNode, HrModelDescInfo& modelDesc)
{


	fbxsdk::FbxMesh* pMesh = (fbxsdk::FbxMesh*)pNode->GetNodeAttribute();
	pMesh->RemoveBadPolygons();

	if (!pMesh->IsTriangleMesh())
	{
		FbxGeometryConverter converter(m_pFbxManager);
		pMesh = (fbxsdk::FbxMesh*)converter.Triangulate(pMesh, true);
	}

	modelDesc.vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
	HrModelDescInfo::HrSubMeshInfo& subMeshInfo = modelDesc.vecSubMeshInfo.back();

	std::string strNodeName = pNode->GetName();
	FbxAMatrix totalMatrix = ComputeTotalMatrix(pNode);
	FbxAMatrix totalMatrixForNormal = totalMatrix.Inverse(); //计算法线
	totalMatrixForNormal = totalMatrixForNormal.Transpose();
	bool bOddNegativeScale = IsOddNegativeScale(totalMatrix);
	bool bVisible = pNode->GetVisibility();

	subMeshInfo.strMeshName = strNodeName;

	bool bAllByControlPoint = true;
	bool bHasNormal = pMesh->GetElementNormalCount() > 0;
	bool bHasUV = pMesh->GetElementUVCount() > 0;
	if (bHasNormal)
	{
		FbxGeometryElement::EMappingMode normalMapppingMode = pMesh->GetElementNormal(0)->GetMappingMode();
		if (normalMapppingMode == FbxGeometryElement::eNone)
		{
			bHasNormal = false;
		}
		else if (normalMapppingMode != FbxGeometryElement::eByControlPoint)
		{
			bAllByControlPoint = false;
		}
	}
	else
	{
		if (pMesh->GetElementNormalCount() < 1 || (pMesh->GetElementNormalCount() > 0 && !pMesh->CheckIfVertexNormalsCCW()))
		{
			bAllByControlPoint = false;
			pMesh->GenerateNormals(true, false, true);
		}
	}

	if (bHasUV)
	{
		FbxGeometryElement::EMappingMode uvMappingMode = pMesh->GetElementUV(0)->GetMappingMode();
		if (uvMappingMode == FbxGeometryElement::eNone)
		{
			bHasUV = false;
		}
		else if (uvMappingMode != FbxGeometryElement::eByControlPoint)
		{
			bAllByControlPoint = false;
		}
	}

	ReadVertexInfo(pMesh, totalMatrix, totalMatrixForNormal, subMeshInfo, bAllByControlPoint, bHasNormal, bHasUV);
	ReadMaterial(pNode, subMeshInfo);
	ReadMaterialConnections(pMesh, subMeshInfo);
	//BOOST_ASSERT(subMeshInfo.vecMaterialInfo.size() == 1);
}

FbxAMatrix HrFBXLoader::ComputeTotalMatrix(fbxsdk::FbxNode* pNode)
{
	FbxVector4 Translation, Rotation, Scaling;
	Translation = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	Rotation = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	Scaling = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix matGeometry;
	matGeometry.SetTRS(Translation, Rotation, Scaling);
	FbxAMatrix& matGlobalTransform = m_pScene->GetAnimationEvaluator()->GetNodeGlobalTransform(pNode);

	FbxAMatrix matTotalMatrix;
	matTotalMatrix = matGlobalTransform * matGeometry;
	return matTotalMatrix;
}

void HrFBXLoader::ReadVertexInfo(fbxsdk::FbxMesh* pMesh
	, FbxAMatrix& totalMatrix
	, fbxsdk::FbxAMatrix& totalMatrixForNormal
	, HrModelDescInfo::HrSubMeshInfo& subMeshInfo
	, bool bAllByControlPoint
	, bool bHasNormal
	, bool bHasUV)
{
	FbxVector4* pControlPoints = pMesh->GetControlPoints();

	if (bAllByControlPoint)
	{
		const FbxGeometryElementNormal* pNormalElement = nullptr;
		if (bHasNormal)
		{
			pNormalElement = pMesh->GetElementNormal(0);
		}
		const FbxGeometryElementUV* pUVElement = nullptr;
		if (bHasUV)
		{
			pUVElement = pMesh->GetElementUV(0);
		}

		int nPolygonVertexCounts = pMesh->GetControlPointsCount();
		for (int nIndex = 0; nIndex < nPolygonVertexCounts; ++nIndex)
		{
			FbxVector4 fbxPosition = pControlPoints[nIndex];
			FbxVector4 finalPosition = totalMatrix.MultT(fbxPosition);
			subMeshInfo.vecVertexPos.emplace_back(Vector3(finalPosition[0], finalPosition[1], finalPosition[2]));

			if (bHasNormal)
			{
				int nNormalIndex = nIndex;
				if (pNormalElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					nNormalIndex = pNormalElement->GetIndexArray().GetAt(nIndex);
				}
				FbxVector4 fbxNormal = pNormalElement->GetDirectArray().GetAt(nNormalIndex);
				FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);
				subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
			}

			if (bHasUV)
			{
				int nUVIndex = nIndex;
				if (pUVElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					nUVIndex = pUVElement->GetIndexArray().GetAt(nIndex);
				}
				FbxVector2 fbxUV = pUVElement->GetDirectArray().GetAt(nUVIndex);
				subMeshInfo.vecUV.emplace_back(Vector2(fbxUV[0], fbxUV[1]));
			}
		}
	}
	else
	{
		const int nPolygonCounts = pMesh->GetPolygonCount();
		for (int nPolygonIndex = 0; nPolygonIndex < nPolygonCounts; ++nPolygonIndex)
		{
			for (int nVerticeIndex = 0; nVerticeIndex < 3; ++nVerticeIndex)
			{
				int nControlPointIndex = pMesh->GetPolygonVertex(nPolygonIndex, nVerticeIndex);
				if (bAllByControlPoint)
				{
					subMeshInfo.vecIndices.push_back(nControlPointIndex);
				}
				else
				{
					subMeshInfo.vecIndices.push_back(nPolygonIndex * 3 + nVerticeIndex);

					FbxVector4 fbxPosition = pControlPoints[nControlPointIndex];
					FbxVector4 finalPosition = totalMatrix.MultT(fbxPosition);
					subMeshInfo.vecVertexPos.emplace_back(Vector3(finalPosition[0], finalPosition[1], finalPosition[2]));

					if (bHasNormal)
					{
						FbxVector4 fbxNormal;
						pMesh->GetPolygonVertexNormal(nPolygonIndex, nVerticeIndex, fbxNormal);
						FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);
						subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
					}
					
					if (bHasUV)
					{
						bool bUnmappedUV;
						FbxVector2 fbxUV;
						const char* pUVName = nullptr;
						pMesh->GetPolygonVertexUV(nPolygonIndex, nVerticeIndex, pUVName, fbxUV, bUnmappedUV);
						subMeshInfo.vecUV.emplace_back(Vector2(fbxUV[0], fbxUV[1]));
					}
				}
			}
		}
	}
}

void HrFBXLoader::ReadMaterialConnections(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	//check whether the material maps with only one mesh
	int nElementMaterialCount = pMesh->GetElementMaterialCount();
	BOOST_ASSERT(nElementMaterialCount == 1);
		
	FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial();
	FbxLayerElementArrayTemplate<int>* pMaterialIndices = &pMesh->GetElementMaterial()->GetIndexArray();

	BOOST_ASSERT(lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame);

	switch (lMaterialElement->GetMappingMode())
	{
	case FbxGeometryElement::eByPolygon:
	{
		//已经按照mesh分割，那么一个mesh按道理应该对应一个material
		int nIndexByPolygonVertex = 0;
		BOOST_ASSERT(pMesh->GetPolygonCount() == pMaterialIndices->GetCount());
		//for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
		//{
		//	int nMaterialIndex = pMaterialIndices->GetAt(nPolygonIndex);
		//	int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
		//	for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
		//	{
		//		++nIndexByPolygonVertex;
		//	}
		//}
		break;
	}
	case FbxGeometryElement::eAllSame:
	{
		//material index
		int nMaterialIndex = pMaterialIndices->GetAt(0);
		//subMeshInfo.nMaterialIndex = nMaterialIndex;
		break;
	}
	}
}



bool HrFBXLoader::IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix)
{
	FbxVector4 Scale = TotalMatrix.GetS();
	int32 NegativeNum = 0;

	if (Scale[0] < 0) NegativeNum++;
	if (Scale[1] < 0) NegativeNum++;
	if (Scale[2] < 0) NegativeNum++;

	return NegativeNum == 1 || NegativeNum == 3;
}

