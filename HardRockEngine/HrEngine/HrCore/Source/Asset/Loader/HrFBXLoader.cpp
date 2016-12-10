#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "fbxsdk.h"

using namespace Hr;

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif

HrFBXLoader::HrFBXLoader()
{

}

HrFBXLoader::~HrFBXLoader()
{
	
}

void HrFBXLoader::Load(std::string& strFile, HrModelDescInfo& modelDesc)
{
	FbxManager* pSdkManager = nullptr;
	FbxScene* pScene = nullptr;
	FbxString fbxFilePath(strFile.c_str());

	InitializeSDKObjects(pSdkManager, pScene);
	if (LoadScene(pSdkManager, pScene, fbxFilePath.Buffer()))
	{
		ParseFBXSdkScene(pScene, modelDesc);
	}

	DestroySdkObjects(pSdkManager, true);
}

void HrFBXLoader::InitializeSDKObjects(FbxManager*& pManager, FbxScene*& pScene)
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	pManager = FbxManager::Create();
	if (!pManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	//FbxString lPath = FbxGetApplicationDirectory();
	//pManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	pScene = FbxScene::Create(pManager, "My Scene");
	if (!pScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}

}

bool HrFBXLoader::LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
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
	FbxImporter* lImporter = FbxImporter::Create(pManager, "");

	// Initialize the importer by providing a filename.
	const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
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
		IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
		IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
		IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
		IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
		IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
		IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
		IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	// Import the scene.
	lStatus = lImporter->Import(pScene);

	if (lStatus == false && lImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::ePasswordError)
	{
		FBXSDK_printf("Please enter password: ");

		lPassword[0] = '\0';

		FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
			scanf("%s", lPassword);
		FBXSDK_CRT_SECURE_NO_WARNING_END

			FbxString lString(lPassword);

		IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
		IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

		lStatus = lImporter->Import(pScene);

		if (lStatus == false && lImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::ePasswordError)
		{
			FBXSDK_printf("\nPassword is wrong, import aborted.\n");
		}
	}

	// Destroy the importer.
	lImporter->Destroy();

	return lStatus;
}

void HrFBXLoader::DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
	//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
	if (pManager) pManager->Destroy();
	if (pExitStatus) FBXSDK_printf("Program Success!\n");
}

void HrFBXLoader::ParseFBXSdkScene(FbxScene* pScene, HrModelDescInfo& modelDesc)
{
	FbxNode* pNode = pScene->GetRootNode();
	if (pNode)
	{
		std::string strNodeName = pNode->GetName();
		FbxVector4 vTranslate = pNode->LclTranslation.Get();
		FbxVector4 vRotation = pNode->LclRotation.Get();
		FbxVector4 vScaling = pNode->LclScaling.Get();
		bool bVisible = pNode->GetVisibility();
		for (int i = 0; i < pNode->GetChildCount(); ++i)
		{
			ParseFBXSdkNode(pNode->GetChild(i), modelDesc);
		}
	}
}

void HrFBXLoader::ParseFBXSdkNode(FbxNode* pNode, HrModelDescInfo& modelDesc)
{
	std::string strNodeName = pNode->GetName();
	FbxVector4 vTranslate = pNode->LclTranslation.Get();
	FbxVector4 vRotation = pNode->LclRotation.Get();
	FbxVector4 vScaling = pNode->LclScaling.Get();
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
	modelDesc.m_vecMeshInfo.emplace_back(HrModelDescInfo::HrMeshInfo());
	HrModelDescInfo::HrMeshInfo& meshInfo = modelDesc.m_vecMeshInfo.back();

	fbxsdk::FbxMesh* pMesh = (fbxsdk::FbxMesh*)pNode->GetNodeAttribute();
	//modelDesc.m_strMeshName = pMesh->GetName();
	meshInfo.strMeshName = pNode->GetName();

	ReadVertexPos(pMesh, meshInfo.m_vecPrimaryPos, meshInfo.m_vecVertexPos);
	ReadIndice(pMesh, meshInfo.m_vecIndice);
	ReadVertexNormal(pMesh, meshInfo.m_vecNormal);
	CalculateAverageNormals(meshInfo);

	ReadColor(pMesh, meshInfo.m_vecColor);
	ReadMaterial(pMesh, meshInfo.m_vecMaterialInfo);
	ReadMaterialConnections(pMesh, meshInfo.m_mapMateialIndexMapIndiceInfo, meshInfo.m_vecSubMeshInfo);


	BuildSubMeshInfo(meshInfo);
	
}

void HrFBXLoader::ReadVertexPos(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecPrimaryPosition, std::vector<Vector3>& vecVertexPosition)
{
	FbxVector4* pControlPoints = pMesh->GetControlPoints();
	for (int nCtrlPointIndex = 0; nCtrlPointIndex < pMesh->GetControlPointsCount(); ++nCtrlPointIndex)
	{
		float x = static_cast<float>(pControlPoints[nCtrlPointIndex][0]);
		float y = static_cast<float>(pControlPoints[nCtrlPointIndex][1]);
		float z = static_cast<float>(pControlPoints[nCtrlPointIndex][2]);

		vecPrimaryPosition.emplace_back(Vector3(x, y, z));
	}

	//for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
	//{
	//	for (int nSizeIndex = 0; nSizeIndex < pMesh->GetPolygonSize(nPolygonIndex); ++nSizeIndex)
	//	{
	//		int nCtrlPointIndex = pMesh->GetPolygonVertex(nPolygonIndex, nSizeIndex);
	//		float x = static_cast<float>(pControlPoints[nCtrlPointIndex][0]);
	//		float y = static_cast<float>(pControlPoints[nCtrlPointIndex][1]);
	//		float z = static_cast<float>(pControlPoints[nCtrlPointIndex][2]);

	//		vecVertexPosition.emplace_back(Vector3(x, y, z));
	//	}
	//}
}

void HrFBXLoader::ReadIndice(fbxsdk::FbxMesh* pMesh, std::vector<uint16>& vecIndices)
{
	int* pIndiceContent = pMesh->GetPolygonVertices();
	for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
	{
		int nIndiceIndexStart = pMesh->GetPolygonVertexIndex(nPolygonIndex);
		for (int nSizeIndex = 0; nSizeIndex < pMesh->GetPolygonSize(nPolygonIndex); ++nSizeIndex)
		{
			vecIndices.push_back(*(pIndiceContent + nIndiceIndexStart + nSizeIndex));
		}
	}
}

void HrFBXLoader::ReadVertexNormal(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecVertexNormal)
{
	if (pMesh->GetElementNormalCount() < 1)
	{
		return;
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
				float x = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexIndex)[0]);
				float y = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexIndex)[1]);
				float z = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexIndex)[2]);
				vecVertexNormal.emplace_back(Vector3(x, y, z));
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

				float x = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[0]);
				float y = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[1]);
				float z = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[2]);
				vecVertexNormal.emplace_back(Vector3(x, y, z));
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
					float x = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nIndexByPolygonVertex)[0]);
					float y = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nIndexByPolygonVertex)[1]);
					float z = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nIndexByPolygonVertex)[2]);
					vecVertexNormal.emplace_back(Vector3(x, y, z));

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

					float x = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[0]);
					float y = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[1]);
					float z = static_cast<float>(pNormalElement->GetDirectArray().GetAt(nVertexNormalIndex)[2]);
					vecVertexNormal.emplace_back(Vector3(x, y, z));

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

void HrFBXLoader::ReadColor(fbxsdk::FbxMesh* pMesh, std::vector<float4>& vecColor)
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
				vecColor.emplace_back(float4(x, y, z, w));
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
				vecColor.emplace_back(float4(x, y, z, w));
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
					vecColor.emplace_back(float4(x, y, z, w));

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
					vecColor.emplace_back(float4(x, y, z, w));

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

void HrFBXLoader::ReadMaterial(fbxsdk::FbxMesh* pMesh, std::vector<HrModelDescInfo::HrMaterialInfo>& vecMaterialInfo)
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
			HrModelDescInfo::HrMaterialInfo materialInfo;

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

				vecMaterialInfo.push_back(materialInfo);
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

				vecMaterialInfo.push_back(materialInfo);
			}

			FbxProperty property;
			//for (int nTextureLayerIndex = 0; nTextureLayerIndex < FbxLayerElement::LAYERELEMENT_TYPE_TEXTURE_COUNT)
			if (pSurfaceMaterial)
			{
				int nTextureIndex;
				FBXSDK_FOR_EACH_TEXTURE(nTextureIndex)
				{
					property = pSurfaceMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[nTextureIndex]);
					if (property.IsValid())
					{
						std::string strName = property.GetName();
						int nTextureCount = property.GetSrcObjectCount<FbxTexture>();
						for (int j = 0; j < nTextureCount; ++j)
						{
							//Here we have to check if it's layeredtextures, or just textures:
							FbxLayeredTexture *lLayeredTexture = property.GetSrcObject<FbxLayeredTexture>(j);
							if (lLayeredTexture)
							{
								int lNbTextures = lLayeredTexture->GetSrcObjectCount<FbxTexture>();
								for (int k = 0; k < lNbTextures; ++k)
								{
									FbxTexture* lTexture = lLayeredTexture->GetSrcObject<FbxTexture>(k);
									if (lTexture)
									{
										//if (pDisplayHeader) {
										//	DisplayInt("    Textures connected to Material ", pMaterialIndex);
										//	pDisplayHeader = false;
										//}
									}
								}
							}
							else
							{
								//no layered texture simply get on the property
								FbxTexture* lTexture = property.GetSrcObject<FbxTexture>(j);
								if (lTexture)
								{
								}
							}
						}
					}
				}
			}
		}
	}
}

void HrFBXLoader::ReadMaterialConnections(fbxsdk::FbxMesh* pMesh, std::map<int, std::vector<int> >& mapMateialIndexMapIndiceInfo, std::vector<HrModelDescInfo::HrSubMeshInfo>& vecSubMeshInfo)
{
	//check whether the material maps with only one mesh
	int nElementMaterialCount = pMesh->GetElementMaterialCount();
	if (nElementMaterialCount > 1)
	{
		nElementMaterialCount = 1;
	}

	
	FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial();
	FbxLayerElementArrayTemplate<int>* pMaterialIndices = &pMesh->GetElementMaterial()->GetIndexArray();

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
				auto item = mapMateialIndexMapIndiceInfo.find(nMaterialIndex);
				if (item == mapMateialIndexMapIndiceInfo.end())
				{
					mapMateialIndexMapIndiceInfo.emplace(std::pair<int, std::vector<int>>(nMaterialIndex, std::vector<int>()));
					item = mapMateialIndexMapIndiceInfo.find(nMaterialIndex);
				}
				item->second.push_back(nIndexByPolygonVertex);

				++nIndexByPolygonVertex;
			}
		}
		break;
	}
	case FbxGeometryElement::eAllSame:
	{
		int nMaterialIndex = pMaterialIndices->GetAt(0);
		int* pIndiceContent = pMesh->GetPolygonVertices();
		mapMateialIndexMapIndiceInfo.emplace(std::pair<int, std::vector<int>>(nMaterialIndex, std::vector<int>()));

		int nIndexByPolygonVertex = 0;
		for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
		{
			int nIndiceIndexStart = pMesh->GetPolygonVertexIndex(nPolygonIndex);
			for (int nSizeIndex = 0; nSizeIndex < pMesh->GetPolygonSize(nPolygonIndex); ++nSizeIndex)
			{
				mapMateialIndexMapIndiceInfo[nMaterialIndex].push_back(nIndexByPolygonVertex++);
			}
		}
		break;
	}
	}
}

void HrFBXLoader::CalculateAverageNormals(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	if (meshInfo.m_vecNormal.empty())
	{
		meshInfo.m_vecNormal.reserve(meshInfo.m_vecPrimaryPos.size());
		for (size_t i = 0; i < meshInfo.m_vecPrimaryPos.size(); ++i)
		{
			meshInfo.m_vecNormal.push_back(Vector3::Zero());
		}
		for (size_t i = 0; i < meshInfo.m_vecIndice.size(); i += 3)
		{
			uint16 nIndex1 = meshInfo.m_vecIndice[i];
			uint16 nIndex2 = meshInfo.m_vecIndice[i + 1];
			uint16 nIndex3 = meshInfo.m_vecIndice[i + 2];

			Vector3 vAB = meshInfo.m_vecPrimaryPos[nIndex2] - meshInfo.m_vecPrimaryPos[nIndex1];
			Vector3 vAC = meshInfo.m_vecPrimaryPos[nIndex3] - meshInfo.m_vecPrimaryPos[nIndex1];

			Vector3 vNormal = HrMath::Cross(vAC, vAB);

			meshInfo.m_vecNormal[nIndex1] += vNormal;
			meshInfo.m_vecNormal[nIndex2] += vNormal;
			meshInfo.m_vecNormal[nIndex3] += vNormal;
		}
		for (size_t i = 0; i < meshInfo.m_vecNormal.size(); ++i)
		{
			meshInfo.m_vecNormal[i] = HrMath::Normalize(meshInfo.m_vecNormal[i]);
		}
	}
}


void HrFBXLoader::BuildSubMeshInfo(HrModelDescInfo::HrMeshInfo& modelDesc)
{
	//暂时先通过Material来拆分Submesh 这里不确定
	if (modelDesc.m_mapMateialIndexMapIndiceInfo.size() == 1)
	{
		modelDesc.m_vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
		auto& subMeshInfo = modelDesc.m_vecSubMeshInfo.back();

		subMeshInfo.nStartIndex = 0;
		subMeshInfo.nIndexSize = modelDesc.m_vecIndice.size();
		subMeshInfo.nMaterialIndex = modelDesc.m_mapMateialIndexMapIndiceInfo.begin()->first;
		subMeshInfo.m_vecPrimaryPos.swap(modelDesc.m_vecPrimaryPos);
		subMeshInfo.m_vecIndice.swap(modelDesc.m_vecIndice);
		subMeshInfo.m_vecNormal.swap(modelDesc.m_vecNormal);
		subMeshInfo.m_vecColor.swap(modelDesc.m_vecColor);

		return;
	}
	for (auto item : modelDesc.m_mapMateialIndexMapIndiceInfo)
	{
		if (item.second.size() > 0)
		{
			modelDesc.m_vecSubMeshInfo.emplace_back(HrModelDescInfo::HrSubMeshInfo());
			auto& subMeshInfo = modelDesc.m_vecSubMeshInfo.back();

			subMeshInfo.nStartIndex = item.second[0];
			subMeshInfo.nIndexSize = item.second.size();

			std::unordered_map<uint32, uint32> mapPrimaryPos;
			for (int i = subMeshInfo.nStartIndex; i < subMeshInfo.nIndexSize; ++i)
			{
				int nVertexIndex = modelDesc.m_vecIndice[i];
				auto item = mapPrimaryPos.find(nVertexIndex);
				if (item != mapPrimaryPos.end())
				{
					subMeshInfo.m_vecIndice.push_back(item->second);
				}
				else
				{
					subMeshInfo.m_vecPrimaryPos.push_back(modelDesc.m_vecPrimaryPos[nVertexIndex]);
					subMeshInfo.m_vecNormal.push_back(modelDesc.m_vecNormal[nVertexIndex]);
					if (!modelDesc.m_vecColor.empty())
						subMeshInfo.m_vecColor.push_back(modelDesc.m_vecColor[nVertexIndex]);

					mapPrimaryPos[nVertexIndex] = subMeshInfo.m_vecPrimaryPos.size() - 1;
					subMeshInfo.m_vecIndice.push_back(subMeshInfo.m_vecPrimaryPos.size() - 1);
				}
			}
		}
	}
}
