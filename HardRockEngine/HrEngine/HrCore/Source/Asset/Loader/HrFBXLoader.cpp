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

void HrFBXLoader::Load(std::string& strFile
	, std::string& strMeshName
	, std::vector<Vector3>& vecPrimaryPos
	, std::vector<Vector3>& vecVertexPos
	, std::vector<uint32>& vecIndice
	, std::vector<Vector3>& vecNormal)
{
	FbxManager* pSdkManager = nullptr;
	FbxScene* pScene = nullptr;
	FbxString fbxFilePath(strFile.c_str());

	InitializeSDKObjects(pSdkManager, pScene);
	if (LoadScene(pSdkManager, pScene, fbxFilePath.Buffer()))
	{
		ParseFBXSdkScene(pScene, strMeshName, vecPrimaryPos, vecVertexPos, vecIndice, vecNormal);
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

		if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
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

	if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
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

		if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
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

void HrFBXLoader::ParseFBXSdkScene(FbxScene* pScene
	, std::string& strMeshName
	, std::vector<Vector3>& vecPrimaryPos
	, std::vector<Vector3>& vecVertexPos
	, std::vector<uint32>& vecIndice
	, std::vector<Vector3>& vecNormal)
{
	FbxNode* pNode = pScene->GetRootNode();
	if (pNode)
	{
		for (int i = 0; i < pNode->GetChildCount(); ++i)
		{
			ParseFBXSdkNode(pNode->GetChild(i), strMeshName, vecPrimaryPos, vecVertexPos, vecIndice, vecNormal);
		}
	}
}

void HrFBXLoader::ParseFBXSdkNode(FbxNode* pNode
	, std::string& strMeshName
	, std::vector<Vector3>& vecPrimaryPos
	, std::vector<Vector3>& vecVertexPos
	, std::vector<uint32>& vecIndice
	, std::vector<Vector3>& vecNormal)
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
			ReadMesh(pNode, strMeshName, vecPrimaryPos, vecVertexPos, vecIndice, vecNormal);
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
}

void HrFBXLoader::ReadMesh(FbxNode* pNode, std::string& strMeshName
	, std::vector<Vector3>& vecPrimaryPos
	, std::vector<Vector3>& vecVertexPos
	, std::vector<uint32>& vecIndice
	, std::vector<Vector3>& vecNormal)
{
	fbxsdk::FbxMesh* pMesh = (fbxsdk::FbxMesh*)pNode->GetNodeAttribute();
	strMeshName = pMesh->GetName();

	ReadVertexPos(pMesh, vecPrimaryPos, vecVertexPos);
	ReadIndice(pMesh, vecIndice);
	ReadVertexNormal(pMesh, vecNormal);
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

	for (int nPolygonIndex = 0; nPolygonIndex < pMesh->GetPolygonCount(); ++nPolygonIndex)
	{
		for (int nSizeIndex = 0; nSizeIndex < pMesh->GetPolygonSize(nPolygonIndex); ++nSizeIndex)
		{
			int nCtrlPointIndex = pMesh->GetPolygonVertex(nPolygonIndex, nSizeIndex);
			float x = static_cast<float>(pControlPoints[nCtrlPointIndex][0]);
			float y = static_cast<float>(pControlPoints[nCtrlPointIndex][1]);
			float z = static_cast<float>(pControlPoints[nCtrlPointIndex][2]);

			vecVertexPosition.emplace_back(Vector3(x, y, z));
		}
	}
}

void HrFBXLoader::ReadIndice(fbxsdk::FbxMesh* pMesh, std::vector<uint32>& vecIndices)
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
