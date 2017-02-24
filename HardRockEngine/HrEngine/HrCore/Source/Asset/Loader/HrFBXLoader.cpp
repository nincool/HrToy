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
		return;
	}

	FbxNode* pNode = m_pScene->GetRootNode();
	if (pNode)
	{
		for (int i = 0; i < pNode->GetChildCount(); ++i)
		{
			ParseFBXSdkNode(pNode->GetChild(i), modelDesc);
		}
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

void HrFBXLoader::ReadMesh(FbxNode* pNode, HrModelDescInfo& modelDesc)
{
	fbxsdk::FbxMesh* pMesh = (fbxsdk::FbxMesh*)pNode->GetNodeAttribute();
	pMesh->RemoveBadPolygons();

	if (!pMesh->IsTriangleMesh())
	{
		FbxGeometryConverter converter(m_pFbxManager);
		pMesh = (fbxsdk::FbxMesh*)converter.Triangulate(pMesh, true);
	}

	modelDesc.meshInfo.vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
	HrModelDescInfo::HrSubMeshInfo& subMeshInfo = modelDesc.meshInfo.vecSubMeshInfo.back();

	std::string strNodeName = pNode->GetName();
	FbxAMatrix totalMatrix = ComputeTotalMatrix(pNode);
	FbxAMatrix totalMatrixForNormal = totalMatrix.Inverse();
	totalMatrixForNormal = totalMatrixForNormal.Transpose();
	bool bOddNegativeScale = IsOddNegativeScale(totalMatrix);
	bool bVisible = pNode->GetVisibility();

	subMeshInfo.strMeshName = strNodeName;

	ReadVertexPos(pMesh, totalMatrix, subMeshInfo);
	ReadVertexNormal(pMesh, totalMatrixForNormal, subMeshInfo);
	ReadVertexUV(pMesh, subMeshInfo);
	ReadMaterial(pMesh, subMeshInfo);
	if (subMeshInfo.vecMaterialInfo.size() > 0)
	{
		ReadMaterialConnections(pMesh);
	}
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

void HrFBXLoader::ReadVertexPos(fbxsdk::FbxMesh* pMesh, FbxAMatrix& totalMatrix, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	FbxVector4* pControlPoints = pMesh->GetControlPoints();

	for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
	{
		BOOST_ASSERT(pMesh->GetPolygonSize(nPolygonIndex) == 3);
		for (int nSizeIndex = 0; nSizeIndex < 3; ++nSizeIndex)
		{
			int nCtrlPointIndex = pMesh->GetPolygonVertex(nPolygonIndex, nSizeIndex);
			FbxVector4 fbxPosition = pControlPoints[nCtrlPointIndex];
			FbxVector4 finalPosition = totalMatrix.MultT(fbxPosition);

			subMeshInfo.vecVertexPos.emplace_back(Vector3(finalPosition[0], finalPosition[1], finalPosition[2]));
		}
	}
}

void HrFBXLoader::ReadVertexNormal(fbxsdk::FbxMesh* pMesh, fbxsdk::FbxAMatrix& totalMatrixForNormal, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	if (pMesh->GetElementNormalCount() < 1 || (pMesh->GetElementNormalCount() > 0 && !pMesh->CheckIfVertexNormalsCCW()))
	{
		pMesh->GenerateNormals(true, false, true);
	}

	FbxGeometryElementNormal* pNormalElement = pMesh->GetElementNormal();
	switch (pNormalElement->GetMappingMode())
	{
	case FbxGeometryElement::eNone:
		break;
	case FbxGeometryElement::eByControlPoint:
	{
		switch (pNormalElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
			{
				FbxVector4 fbxNormal = pNormalElement->GetDirectArray().GetAt(nVertexIndex);
				FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);

				subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
			}
			break;
		}
		case FbxGeometryElement::eIndex:
		{
			break;
		}
		case FbxGeometryElement::eIndexToDirect:
		{
			for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
			{
				int nVertexNormalIndex = pNormalElement->GetIndexArray().GetAt(nVertexIndex);
				FbxVector4 fbxNormal = pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex);
				FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);

				subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (pNormalElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			int nIndexByPolygonVertex = 0;
			for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
			{
				int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
				for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
				{
					FbxVector4 fbxNormal = pNormalElement->GetDirectArray().GetAt(nIndexByPolygonVertex);
					FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);

					subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
					++nIndexByPolygonVertex;
				}
			}
			break;
		}
		case FbxGeometryElement::eIndex:
		{
			break;
		}
		case FbxGeometryElement::eIndexToDirect:
		{
			int nIndexByPolygonVertex = 0;
			for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
			{
				int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
				for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
				{
					int nVertexNormalIndex = pNormalElement->GetIndexArray().GetAt(nIndexByPolygonVertex);

					FbxVector4 fbxNormal = pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex);
					FbxVector4 finalNormal = totalMatrixForNormal.MultT(fbxNormal);

					subMeshInfo.vecNormal.emplace_back(Vector3(finalNormal[0], finalNormal[1], finalNormal[2]));
					++nIndexByPolygonVertex;
				}
			}
			break;
		}
		default:
			break;
		}

		break;
	}
	case FbxGeometryElement::eByPolygon:
		break;
	case FbxGeometryElement::eByEdge:
		break;
	case FbxGeometryElement::eAllSame:
		break;
	default:
		break;
	}
}

void HrFBXLoader::ReadVertexColor(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	if (pMesh->GetElementVertexColorCount() < 1)
	{
		return;
	}

	FbxGeometryElementVertexColor* pVertexColor = pMesh->GetElementVertexColor();
	switch (pVertexColor->GetMappingMode())
	{
	case FbxGeometryElement::eNone:
		break;
	case FbxGeometryElement::eByControlPoint:
	{
		switch (pVertexColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
			{
				float x = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexIndex).mRed);
				float y = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexIndex).mGreen);
				float z = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexIndex).mBlue);
				float w = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexIndex).mAlpha);
				subMeshInfo.vecColor.emplace_back(float4(x, y, z, w));
			}
			break;
		}
		case FbxGeometryElement::eIndex:
		{
			break;
		}
		case FbxGeometryElement::eIndexToDirect:
		{
			for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
			{
				int nVertexNormalIndex = pVertexColor->GetIndexArray().GetAt(nVertexIndex);

				float x = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mRed);
				float y = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mGreen);
				float z = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mBlue);
				float w = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mAlpha);
				subMeshInfo.vecColor.emplace_back(float4(x, y, z, w));
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (pVertexColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			int nIndexByPolygonVertex = 0;
			for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
			{
				int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
				for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
				{
					float x = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nIndexByPolygonVertex).mRed);
					float y = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nIndexByPolygonVertex).mGreen);
					float z = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nIndexByPolygonVertex).mBlue);
					float w = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nIndexByPolygonVertex).mAlpha);
					subMeshInfo.vecColor.emplace_back(float4(x, y, z, w));

					++nIndexByPolygonVertex;
				}
			}
			break;
		}
		case FbxGeometryElement::eIndex:
		{
			break;
		}
		case FbxGeometryElement::eIndexToDirect:
		{
			int nIndexByPolygonVertex = 0;
			for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
			{
				int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
				for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
				{
					int nVertexNormalIndex = pVertexColor->GetIndexArray().GetAt(nIndexByPolygonVertex);
					float x = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mRed);
					float y = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mGreen);
					float z = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mBlue);
					float w = static_cast<float>(pVertexColor->GetDirectArray().GetAt(nVertexNormalIndex).mAlpha);
					subMeshInfo.vecColor.emplace_back(float4(x, y, z, w));

					++nIndexByPolygonVertex;
				}
			}
			break;
		}
		default:
			break;
		}

		break;
	}
	case FbxGeometryElement::eByPolygon:
		break;
	case FbxGeometryElement::eByEdge:
		break;
	case FbxGeometryElement::eAllSame:
		break;
	default:
		break;
	}
}

void HrFBXLoader::ReadVertexUV(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	int32 nLayerCount = pMesh->GetLayerCount();
	for (int i = 0; i < nLayerCount; ++i)
	{
		FbxLayer* pLayer = pMesh->GetLayer(i);
		int nUVSetCount = pLayer->GetUVSetCount();
		if (nUVSetCount > 0)
		{
			FbxArray<FbxLayerElementUV const*> eleUVs = pLayer->GetUVSets();
			for (int nIndex = 0; nIndex < nUVSetCount; ++nIndex)
			{
				FbxLayerElementUV const* pElementUV = eleUVs[nIndex];
				if (pElementUV)
				{
					const char* pUVSetName = pElementUV->GetName();
					std::string strUVSetName = pUVSetName;
				}
			}
		}
	}
	for (int l = 0; l < pMesh->GetElementUVCount(); ++l)
	{
		FbxGeometryElementUV* leUV = pMesh->GetElementUV(l);

		switch (leUV->GetMappingMode())
		{
		default:
			break;
		case FbxGeometryElement::eByControlPoint:
			switch (leUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
				{
					float x = static_cast<float>(leUV->GetDirectArray().GetAt(nVertexIndex)[0]);
					float y = 1.0f - static_cast<float>(leUV->GetDirectArray().GetAt(nVertexIndex)[1]);//flip the Y of UVs for DirectX from UE4
					subMeshInfo.vecTexCoord.emplace_back(float2(x, y));
				}
				break;
			case FbxGeometryElement::eIndexToDirect:
			{
				for (int nVertexIndex = 0; nVertexIndex < pMesh->GetControlPointsCount(); ++nVertexIndex)
				{
					int nVertexNormalIndex = leUV->GetIndexArray().GetAt(nVertexIndex);

					float x = static_cast<float>(leUV->GetDirectArray().GetAt(nVertexNormalIndex)[0]);
					float y = 1.0f - static_cast<float>(leUV->GetDirectArray().GetAt(nVertexNormalIndex)[1]);//flip the Y of UVs for DirectX from UE4
					subMeshInfo.vecTexCoord.emplace_back(float2(x, y));
				}
			}
			break;
			default:
				break; // other reference modes not shown here!
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (leUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			case FbxGeometryElement::eIndexToDirect:
			{
				for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
				{
					int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
					for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
					{
						int nTextureIndex = pMesh->GetTextureUVIndex(nPolygonIndex, nSizeIndex);
						float x = static_cast<float>(leUV->GetDirectArray().GetAt(nTextureIndex)[0]);
						float y = 1.0f - static_cast<float>(leUV->GetDirectArray().GetAt(nTextureIndex)[1]);//flip the Y of UVs for DirectX from UE4
						subMeshInfo.vecTexCoord.emplace_back(float2(x, y));
					}
				}
			}
			break;
			default:
				break; // other reference modes not shown here!
			}
		}
		break;

		case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
		case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
		case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
			break;
		}
	}
}

void HrFBXLoader::ReadMaterial(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo)
{
	int nMaterialCount = 0;
	FbxNode* pNode = pMesh->GetNode();
	if (pNode)
	{
		nMaterialCount = pNode->GetMaterialCount();
	}
	if (nMaterialCount > 0)
	{
		FbxPropertyT<FbxDouble3> lKFbxDouble3;
		FbxPropertyT<FbxDouble> lKFbxDouble1;
		FbxColor theColor;

		for (int nMaterialIndex = 0; nMaterialIndex < nMaterialCount; ++nMaterialIndex)
		{
			subMeshInfo.vecMaterialInfo.emplace_back(HrModelDescInfo::HrMaterialInfo());
			HrModelDescInfo::HrMaterialInfo& materialInfo = subMeshInfo.vecMaterialInfo.back();

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

				// Emissive Color
				lKFbxDouble3 = ((FbxSurfacePhong*)pSurfaceMaterial)->Emissive;
				materialInfo.v4Emissive.x() = lKFbxDouble3.Get()[0];
				materialInfo.v4Emissive.y() = lKFbxDouble3.Get()[1];
				materialInfo.v4Emissive.z() = lKFbxDouble3.Get()[2];
				materialInfo.v4Emissive.w() = 1.0f;

				// Opacity
				lKFbxDouble1 = ((FbxSurfacePhong*)pSurfaceMaterial)->TransparencyFactor;
				materialInfo.fOpacity = lKFbxDouble1.Get();

			}

			FbxProperty property;
			if (pSurfaceMaterial)
			{
				int nTextureIndex;
				FBXSDK_FOR_EACH_TEXTURE(nTextureIndex)
				{
					property = pSurfaceMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[nTextureIndex]);
					if (property.IsValid())
					{
						//Here we have to check if it's layered textures, or just textures:
						int32 LayeredTextureCount = property.GetSrcObjectCount<FbxLayeredTexture>();
						FbxString PropertyName = property.GetName();
						if (LayeredTextureCount > 0)
						{
							for (int32 LayerIndex = 0; LayerIndex < LayeredTextureCount; ++LayerIndex)
							{
								FbxLayeredTexture *lLayeredTexture = property.GetSrcObject<FbxLayeredTexture>(LayerIndex);
								int32 NbTextures = lLayeredTexture->GetSrcObjectCount<FbxTexture>();
								for (int32 TexIndex = 0; TexIndex < NbTextures; ++TexIndex)
								{
									FbxFileTexture* Texture = lLayeredTexture->GetSrcObject<FbxFileTexture>(TexIndex);
									if (Texture)
									{
										std::string Filename1 = Texture->GetFileName();
										if (std::find_if(subMeshInfo.vecTextureFileName.begin(), subMeshInfo.vecTextureFileName.end(), [&](std::string& item) {return (item == Filename1); }) == subMeshInfo.vecTextureFileName.end())
										{
											subMeshInfo.vecTextureFileName.push_back(Filename1);
										}
									}
								}
							}
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
									if (std::find_if(subMeshInfo.vecTextureFileName.begin(), subMeshInfo.vecTextureFileName.end(), [&](std::string& item) {return (item == Filename1); }) == subMeshInfo.vecTextureFileName.end())
									{
										subMeshInfo.vecTextureFileName.push_back(Filename1);
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

void HrFBXLoader::ReadMaterialConnections(fbxsdk::FbxMesh* pMesh)
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
		int nIndexByPolygonVertex = 0;
		BOOST_ASSERT(pMesh->GetPolygonCount() == pMaterialIndices->GetCount());
		for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
		{
			int nMaterialIndex = pMaterialIndices->GetAt(nPolygonIndex);
			int nPolygonSize = pMesh->GetPolygonSize(nPolygonIndex);
			for (int nSizeIndex = 0; nSizeIndex < nPolygonSize; ++nSizeIndex)
			{
				++nIndexByPolygonVertex;
			}
		}
		break;
	}
	case FbxGeometryElement::eAllSame:
	{
		int nMaterialIndex = pMaterialIndices->GetAt(0);
		int* pIndiceContent = pMesh->GetPolygonVertices();
		break;
	}
	}
}

//void HrFBXLoader::CalculateAverageNormals(HrModelDescInfo::HrMeshInfo& meshInfo)
//{
//	if (meshInfo.m_vecNormal.empty())
//	{
//		meshInfo.m_vecNormal.reserve(meshInfo.m_vecPrimaryPos.size());
//		for (size_t i = 0; i < meshInfo.m_vecPrimaryPos.size(); ++i)
//		{
//			meshInfo.m_vecNormal.push_back(Vector3::Zero());
//		}
//		for (size_t i = 0; i < meshInfo.m_vecIndice.size(); i += 3)
//		{
//			uint16 nIndex1 = meshInfo.m_vecIndice[i];
//			uint16 nIndex2 = meshInfo.m_vecIndice[i + 1];
//			uint16 nIndex3 = meshInfo.m_vecIndice[i + 2];
//
//			Vector3 vAB = meshInfo.m_vecPrimaryPos[nIndex2] - meshInfo.m_vecPrimaryPos[nIndex1];
//			Vector3 vAC = meshInfo.m_vecPrimaryPos[nIndex3] - meshInfo.m_vecPrimaryPos[nIndex1];
//
//			Vector3 vNormal = HrMath::Cross(vAC, vAB);
//
//			meshInfo.m_vecNormal[nIndex1] += vNormal;
//			meshInfo.m_vecNormal[nIndex2] += vNormal;
//			meshInfo.m_vecNormal[nIndex3] += vNormal;
//		}
//		for (size_t i = 0; i < meshInfo.m_vecNormal.size(); ++i)
//		{
//			meshInfo.m_vecNormal[i] = HrMath::Normalize(meshInfo.m_vecNormal[i]);
//		}
//	}
//	else
//	{
//		std::vector<Vector3> vecNormal(std::move(meshInfo.m_vecNormal));
//		meshInfo.m_vecNormal.clear();
//		meshInfo.m_vecNormal.reserve(meshInfo.m_vecPrimaryPos.size());
//		for (size_t i = 0; i < meshInfo.m_vecPrimaryPos.size(); ++i)
//		{
//			meshInfo.m_vecNormal.push_back(Vector3::Zero());
//		}
//		for (size_t i = 0; i < meshInfo.m_vecIndice.size(); i += 3)
//		{
//			uint16 nIndex1 = meshInfo.m_vecIndice[i];
//			uint16 nIndex2 = meshInfo.m_vecIndice[i + 1];
//			uint16 nIndex3 = meshInfo.m_vecIndice[i + 2];
//
//
//			meshInfo.m_vecNormal[nIndex1] += vecNormal[nIndex1];
//			meshInfo.m_vecNormal[nIndex2] += vecNormal[nIndex1];
//			meshInfo.m_vecNormal[nIndex3] += vecNormal[nIndex1];
//		}
//		for (size_t i = 0; i < meshInfo.m_vecNormal.size(); ++i)
//		{
//			meshInfo.m_vecNormal[i] = HrMath::Normalize(meshInfo.m_vecNormal[i]);
//		}
//	}
//}


//void HrFBXLoader::BuildSubMeshInfo(HrModelDescInfo::HrMeshInfo& modelDesc)
//{
//	//暂时先通过Material来拆分Submesh 这里不确定
//	if (modelDesc.m_mapMateialIndexMapIndiceInfo.size() == 1)
//	{
//		modelDesc.m_vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
//		auto& subMeshInfo = modelDesc.m_vecSubMeshInfo.back();
//
//		subMeshInfo.nStartIndex = 0;
//		subMeshInfo.nIndexSize = modelDesc.m_vecIndice.size();
//		subMeshInfo.nMaterialIndex = modelDesc.m_mapMateialIndexMapIndiceInfo.begin()->first;
//		subMeshInfo.m_vecPrimaryPos.swap(modelDesc.m_vecPrimaryPos);
//		subMeshInfo.m_vecVertexPos.swap(modelDesc.m_vecVertexPos);
//		subMeshInfo.m_vecIndice.swap(modelDesc.m_vecIndice);
//		subMeshInfo.m_vecNormal.swap(modelDesc.m_vecNormal);
//		subMeshInfo.m_vecColor.swap(modelDesc.m_vecColor);
//		subMeshInfo.m_vecTexCoord.swap(modelDesc.m_vecUV);
//
//		return;
//	}
//	for (auto item : modelDesc.m_mapMateialIndexMapIndiceInfo)
//	{
//		if (item.second.size() > 0)
//		{
//			modelDesc.m_vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
//			auto& subMeshInfo = modelDesc.m_vecSubMeshInfo.back();
//
//			subMeshInfo.nStartIndex = item.second[0];
//			subMeshInfo.nIndexSize = item.second.size();
//
//			std::unordered_map<uint32, uint32> mapPrimaryPos;
//			for (int i = subMeshInfo.nStartIndex; i < subMeshInfo.nIndexSize; ++i)
//			{
//				int nVertexIndex = modelDesc.m_vecIndice[i];
//				auto item = mapPrimaryPos.find(nVertexIndex);
//				if (item != mapPrimaryPos.end())
//				{
//					subMeshInfo.m_vecIndice.push_back(item->second);
//				}
//				else
//				{
//					subMeshInfo.m_vecPrimaryPos.push_back(modelDesc.m_vecPrimaryPos[nVertexIndex]);
//					subMeshInfo.m_vecNormal.push_back(modelDesc.m_vecNormal[nVertexIndex]);
//					if (!modelDesc.m_vecColor.empty())
//						subMeshInfo.m_vecColor.push_back(modelDesc.m_vecColor[nVertexIndex]);
//					if (!modelDesc.m_vecUV.empty())
//						subMeshInfo.m_vecTexCoord.push_back(modelDesc.m_vecUV[nVertexIndex]);
//					mapPrimaryPos[nVertexIndex] = subMeshInfo.m_vecPrimaryPos.size() - 1;
//					subMeshInfo.m_vecIndice.push_back(subMeshInfo.m_vecPrimaryPos.size() - 1);
//				}
//			}
//		}
//	}
//}

bool HrFBXLoader::IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix)
{
	FbxVector4 Scale = TotalMatrix.GetS();
	int32 NegativeNum = 0;

	if (Scale[0] < 0) NegativeNum++;
	if (Scale[1] < 0) NegativeNum++;
	if (Scale[2] < 0) NegativeNum++;

	return NegativeNum == 1 || NegativeNum == 3;
}

