#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "Asset/Loader/HrFBXUtilsImport.h"
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
		//ParseFBXSdkScene(modelDesc);
		LoadCacheRecursive(m_pScene, nullptr, nullptr, true, modelDesc);
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

FbxAMatrix HrFBXLoader::ComputeTotalMatrix(fbxsdk::FbxNode* pNode)
{
	FbxAMatrix Geometry;
	FbxVector4 Translation, Rotation, Scaling;
	Translation = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	Rotation = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	Scaling = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	Geometry.SetT(Translation);
	Geometry.SetR(Rotation);
	Geometry.SetS(Scaling);

	//For Single Matrix situation, obtain transfrom matrix from eDESTINATION_SET, which include pivot offsets and pre/post rotations.
	FbxAMatrix& GlobalTransform = m_pScene->GetAnimationEvaluator()->GetNodeGlobalTransform(pNode);

	FbxAMatrix TotalMatrix;
	TotalMatrix = GlobalTransform * Geometry;

	return TotalMatrix;
}

bool HrFBXLoader::IsOddNegativeScale(FbxAMatrix& TotalMatrix)
{
	FbxVector4 Scale = TotalMatrix.GetS();
	int32 NegativeNum = 0;

	if (Scale[0] < 0) NegativeNum++;
	if (Scale[1] < 0) NegativeNum++;
	if (Scale[2] < 0) NegativeNum++;

	return NegativeNum == 1 || NegativeNum == 3;
}


bool HrFBXLoader::IsAllIndices(HrModelDescInfo::HrSubMeshInfo& meshInfo)
{
	//int nVertexPosSize = meshInfo.vecVertexPos.size();
	//bool bIndexNormal = ((meshInfo.vecNormal.size() > 0 && meshInfo.vecNormal.size() == nVertexPosSize) || meshInfo.vecNormal.size() == 0);
	//bool bIndexTangent = ((meshInfo.vecTangent.size() > 0 && meshInfo.vecTangent.size() == nVertexPosSize) || meshInfo.vecTangent.size() == 0);
	//bool bIndexBinormal = ((meshInfo.vecBinormal.size() > 0 && meshInfo.vecBinormal.size() == nVertexPosSize) || meshInfo.vecBinormal.size() == 0);
	//bool bIndexUV = ((meshInfo.vecUV.size() > 0 && meshInfo.vecUV.size() == nVertexPosSize) || meshInfo.vecUV.size() == 0);

	//meshInfo.bIndexDataType16bit = false;
	//meshInfo.bAllIndices = (bIndexNormal && bIndexTangent && bIndexBinormal && bIndexUV);
	//if (meshInfo.bAllIndices)
	//{
	//	meshInfo.bIndexDataType16bit = nVertexPosSize <= std::numeric_limits<uint16>::max();
	//}

	//return meshInfo.bAllIndices;

	return false;
}

void Hr::HrFBXLoader::LoadCacheRecursive(fbxsdk::FbxScene * pScene, fbxsdk::FbxAnimLayer * pAnimLayer, const char * pFbxFileName, bool pSupportVBO, HrModelDescInfo& modelDesc)
{
	// Load the textures into GPU, only for file texture now
	const int lTextureCount = pScene->GetTextureCount();
	for (int lTextureIndex = 0; lTextureIndex < lTextureCount; ++lTextureIndex)
	{
		FbxTexture * lTexture = pScene->GetTexture(lTextureIndex);
		FbxFileTexture * lFileTexture = FbxCast<FbxFileTexture>(lTexture);
		if (lFileTexture && !lFileTexture->GetUserDataPtr())
		{
			// Try to load the texture from absolute path
			const FbxString lFileName = lFileTexture->GetFileName();

			// Only TGA textures are supported now.
			if (lFileName.Right(3).Upper() != "TGA")
			{
				FBXSDK_printf("Only TGA textures are supported now: %s\n", lFileName.Buffer());
				continue;
			}

			//GLuint lTextureObject = 0;
			bool lStatus = true;//LoadTextureFromFile(lFileName, lTextureObject);

			//const FbxString lAbsFbxFileName = FbxPathUtils::Resolve(pFbxFileName);
			//const FbxString lAbsFolderName = FbxPathUtils::GetFolderName(lAbsFbxFileName);
			if (!lStatus)
			{
				// Load texture from relative file name (relative to FBX file)
				//const FbxString lResolvedFileName = FbxPathUtils::Bind(lAbsFolderName, lFileTexture->GetRelativeFileName());
				//lStatus = LoadTextureFromFile(lResolvedFileName, lTextureObject);
			}

			if (!lStatus)
			{
				// Load texture from file name only (relative to FBX file)
				//const FbxString lTextureFileName = FbxPathUtils::GetFileName(lFileName);
				//const FbxString lResolvedFileName = FbxPathUtils::Bind(lAbsFolderName, lTextureFileName);
				//lStatus = LoadTextureFromFile(lResolvedFileName, lTextureObject);
			}

			if (!lStatus)
			{
				FBXSDK_printf("Failed to load texture file: %s\n", lFileName.Buffer());
				continue;
			}

			if (lStatus)
			{
				//GLuint * lTextureName = new GLuint(lTextureObject);
				//lFileTexture->SetUserDataPtr(lTextureName);
			}
		}
	}

	LoadCacheRecursive(pScene->GetRootNode(), pAnimLayer, pSupportVBO, modelDesc);
}


fbxsdk::FbxAMatrix HrFBXLoader::GetGlobalPosition(fbxsdk::FbxNode* pNode, const fbxsdk::FbxTime& pTime, fbxsdk::FbxPose* pPose, fbxsdk::FbxAMatrix* pParentGlobalPosition)
{
	FbxAMatrix lGlobalPosition;
	bool        lPositionFound = false;

	if (pPose)
	{
		int lNodeIndex = pPose->Find(pNode);

		if (lNodeIndex > -1)
		{
			// The bind pose is always a global matrix.
			// If we have a rest pose, we need to check if it is
			// stored in global or local space.
			if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
			{
				lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
			}
			else
			{
				// We have a local matrix, we need to convert it to
				// a global space matrix.
				FbxAMatrix lParentGlobalPosition;

				if (pParentGlobalPosition)
				{
					lParentGlobalPosition = *pParentGlobalPosition;
				}
				else
				{
					if (pNode->GetParent())
					{
						lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
					}
				}

				FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
				lGlobalPosition = lParentGlobalPosition * lLocalPosition;
			}

			lPositionFound = true;
		}
	}

	if (!lPositionFound)
	{
		// There is no pose entry for that node, get the current global position instead.

		// Ideally this would use parent global position and local position to compute the global position.
		// Unfortunately the equation 
		//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
		// does not hold when inheritance type is other than "Parent" (RSrs).
		// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
		lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
	}

	return lGlobalPosition;
}

fbxsdk::FbxAMatrix HrFBXLoader::GetPoseMatrix(fbxsdk::FbxPose* pPose, int pNodeIndex)
{
	FbxAMatrix lPoseMatrix;
	FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

	memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

	return lPoseMatrix;
}

void HrFBXLoader::LoadCacheRecursive(fbxsdk::FbxNode * pNode, fbxsdk::FbxAnimLayer * pAnimLayer, bool pSupportVBO, HrModelDescInfo& modelDesc)
{
	// Bake material and hook as user data.
	const int lMaterialCount = pNode->GetMaterialCount();
	for (int lMaterialIndex = 0; lMaterialIndex < lMaterialCount; ++lMaterialIndex)
	{
		FbxSurfaceMaterial * lMaterial = pNode->GetMaterial(lMaterialIndex);
		if (lMaterial && !lMaterial->GetUserDataPtr())
		{
			//FbxAutoPtr<MaterialCache> lMaterialCache(new MaterialCache);
			//if (lMaterialCache->Initialize(lMaterial))
			//{
			//	lMaterial->SetUserDataPtr(lMaterialCache.Release());
			//}
		}
	}

	FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
	if (lNodeAttribute)
	{
		// Bake mesh as VBO(vertex buffer object) into GPU.
		if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			FbxMesh * lMesh = pNode->GetMesh();
			if (pSupportVBO && lMesh && !lMesh->GetUserDataPtr())
			{
				InitializeSubMesh(lMesh, modelDesc);
			}
		}
		// Bake light properties.
		else if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eLight)
		{
			FbxLight * lLight = pNode->GetLight();
			if (lLight && !lLight->GetUserDataPtr())
			{
				//FbxAutoPtr<LightCache> lLightCache(new LightCache);
				//if (lLightCache->Initialize(lLight, pAnimLayer))
				//{
				//	lLight->SetUserDataPtr(lLightCache.Release());
				//}
			}
		}
	}

	const int lChildCount = pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		LoadCacheRecursive(pNode->GetChild(lChildIndex), pAnimLayer, pSupportVBO, modelDesc);
	}
}


bool HrFBXLoader::InitializeSubMesh(fbxsdk::FbxMesh* pMesh, HrModelDescInfo& modelDesc)
{
	if (!pMesh->GetNode())
		return false;

	bool bCCW = (const_cast<fbxsdk::FbxMesh*>(pMesh))->CheckIfVertexNormalsCCW();

	std::string strMeshName = pMesh->GetNode()->GetName();
	const int lPolygonCount = pMesh->GetPolygonCount();

	// Count the polygon count of each material
	FbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
	FbxGeometryElement::EMappingMode lMaterialMappingMode = FbxGeometryElement::eNone;
	if (pMesh->GetElementMaterial())
	{
		lMaterialIndice = &pMesh->GetElementMaterial()->GetIndexArray();
		lMaterialMappingMode = pMesh->GetElementMaterial()->GetMappingMode();
		if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
		{
			FBX_ASSERT(lMaterialIndice->GetCount() == lPolygonCount);
			if (lMaterialIndice->GetCount() == lPolygonCount)
			{
				// Count the faces of each material
				for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
				{
					const int lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
					if (modelDesc.vecSubMeshInfo.size() < lMaterialIndex + 1)
					{
						modelDesc.vecSubMeshInfo.resize(lMaterialIndex + 1);
					}

					modelDesc.vecSubMeshInfo[lMaterialIndex].nTriangleCount += 1;
				}

				// Make sure we have no "holes" (NULL) in the mSubMeshes table. This can happen
				// if, in the loop above, we resized the mSubMeshes by more than one slot.
				//for (int i = 0; i < mSubMeshes.GetCount(); i++)
				//{
				//	if (mSubMeshes[i] == NULL)
				//		mSubMeshes[i] = new SubMesh;
				//}

				// Record the offset (how many vertex)
				const int lMaterialCount = modelDesc.vecSubMeshInfo.size();
				int lOffset = 0;
				for (int lIndex = 0; lIndex < lMaterialCount; ++lIndex)
				{
					modelDesc.vecSubMeshInfo[lIndex].nIndexOffset = lOffset;
					lOffset += modelDesc.vecSubMeshInfo[lIndex].nTriangleCount * 3;
					// This will be used as counter in the following procedures, reset to zero
					modelDesc.vecSubMeshInfo[lIndex].nTriangleCount = 0;
				}
				FBX_ASSERT(lOffset == lPolygonCount * 3);
			}
		}
	}

	// All faces will use the same material.
	if (modelDesc.vecSubMeshInfo.size() == 0)
	{
		modelDesc.vecSubMeshInfo.resize(1);
		modelDesc.vecSubMeshInfo[0].strMeshName = strMeshName;
	}

	fbxsdk::FbxAMatrix TotalMatrix;
	fbxsdk::FbxAMatrix TotalMatrixForNormal;
	TotalMatrix = ComputeTotalMatrix(pMesh->GetNode());
	TotalMatrixForNormal = TotalMatrix.Inverse();
	TotalMatrixForNormal = TotalMatrixForNormal.Transpose();

	bool OddNegativeScale = IsOddNegativeScale(TotalMatrix);

	// Congregate all the data of a mesh to be cached in VBOs.
	// If normal or UV is by polygon vertex, record all vertex attributes by polygon vertex.
	mHasNormal = pMesh->GetElementNormalCount() > 0;
	mHasUV = pMesh->GetElementUVCount() > 0;
	FbxGeometryElement::EMappingMode lNormalMappingMode = FbxGeometryElement::eNone;
	FbxGeometryElement::EMappingMode lUVMappingMode = FbxGeometryElement::eNone;
	if (mHasNormal)
	{
		lNormalMappingMode = pMesh->GetElementNormal(0)->GetMappingMode();
		if (lNormalMappingMode == FbxGeometryElement::eNone)
		{
			mHasNormal = false;
		}
		if (mHasNormal && lNormalMappingMode != FbxGeometryElement::eByControlPoint)
		{
			mAllByControlPoint = false;
		}
	}
	if (mHasUV)
	{
		lUVMappingMode = pMesh->GetElementUV(0)->GetMappingMode();
		if (lUVMappingMode == FbxGeometryElement::eNone)
		{
			mHasUV = false;
		}
		if (mHasUV && lUVMappingMode != FbxGeometryElement::eByControlPoint)
		{
			mAllByControlPoint = false;
		}
	}

	// Allocate the array memory, by control point or by polygon vertex.
	int lPolygonVertexCount = pMesh->GetControlPointsCount();
	if (!mAllByControlPoint)
	{
		lPolygonVertexCount = lPolygonCount * TRIANGLE_VERTEX_COUNT;
	}
	//float * lVertices = new float[lPolygonVertexCount * VERTEX_STRIDE];
	modelDesc.vecVertexPos.resize(lPolygonVertexCount);
	//unsigned int * lIndices = new unsigned int[lPolygonCount * TRIANGLE_VERTEX_COUNT];
	modelDesc.vecIndices.resize(lPolygonCount * TRIANGLE_VERTEX_COUNT);
	//float * lNormals = NULL;
	if (mHasNormal)
	{
		//lNormals = new float[lPolygonVertexCount * NORMAL_STRIDE];
		modelDesc.vecNormal.resize(lPolygonVertexCount);
	}
	//float * lUVs = NULL;
	FbxStringList lUVNames;
	pMesh->GetUVSetNames(lUVNames);
	const char * lUVName = NULL;
	if (mHasUV && lUVNames.GetCount())
	{
		//lUVs = new float[lPolygonVertexCount * UV_STRIDE];
		modelDesc.vecUV.resize(lPolygonVertexCount);
		lUVName = lUVNames[0];
	}

	// Populate the array with vertex attribute, if by control point.
	const FbxVector4 * lControlPoints = pMesh->GetControlPoints();
	FbxVector4 lCurrentVertex;
	FbxVector4 lCurrentNormal;
	FbxVector2 lCurrentUV;
	if (mAllByControlPoint)
	{
		const FbxGeometryElementNormal * lNormalElement = NULL;
		const FbxGeometryElementUV * lUVElement = NULL;
		if (mHasNormal)
		{
			lNormalElement = pMesh->GetElementNormal(0);
		}
		if (mHasUV)
		{
			lUVElement = pMesh->GetElementUV(0);
		}
		for (int lIndex = 0; lIndex < lPolygonVertexCount; ++lIndex)
		{
			// Save the vertex position.
			lCurrentVertex = lControlPoints[lIndex];
			Vector3 finalPosition = HrFBXDataConverter::ConvertPos(TotalMatrix.MultT(lCurrentVertex));
			modelDesc.vecVertexPos[lIndex] = finalPosition;

			// Save the normal.
			if (mHasNormal)
			{
				int lNormalIndex = lIndex;
				if (lNormalElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndex);
				}
				lCurrentNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
				Vector3 finalNormal = HrFBXDataConverter::ConvertDir(TotalMatrixForNormal.MultT(lCurrentNormal));
				modelDesc.vecNormal[lIndex] = finalNormal;
			}

			// Save the UV.
			if (mHasUV)
			{
				int lUVIndex = lIndex;
				if (lUVElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					lUVIndex = lUVElement->GetIndexArray().GetAt(lIndex);
				}
				lCurrentUV = lUVElement->GetDirectArray().GetAt(lUVIndex);
				modelDesc.vecUV[lIndex] = Vector2(static_cast<float>(lCurrentUV[0]), static_cast<float>(lCurrentUV[1]));
			}
		}

	}

	int lVertexCount = 0;
	for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex)
	{
		// The material for current face.
		int lMaterialIndex = 0;
		if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
		{
			lMaterialIndex = lMaterialIndice->GetAt(lPolygonIndex);
		}

		// Where should I save the vertex attribute index, according to the material
		const int lIndexOffset = modelDesc.vecSubMeshInfo[lMaterialIndex].nIndexOffset +
			modelDesc.vecSubMeshInfo[lMaterialIndex].nTriangleCount * 3;
		for (int lVerticeIndex = 0; lVerticeIndex < 3; ++lVerticeIndex)
		{
			const int lControlPointIndex = pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex);

			if (mAllByControlPoint)
			{
				modelDesc.vecIndices[lIndexOffset + lVerticeIndex] = static_cast<unsigned int>(lControlPointIndex);
			}
			// Populate the array with vertex attribute, if by polygon vertex.
			else
			{
				modelDesc.vecIndices[lIndexOffset + lVerticeIndex] = static_cast<unsigned int>(lVertexCount);

				lCurrentVertex = lControlPoints[lControlPointIndex];
				fbxsdk::FbxVector4 finalPosition = TotalMatrix.MultT(lCurrentVertex);
				modelDesc.vecVertexPos[lVertexCount] = Vector3(static_cast<float>(finalPosition[0]), static_cast<float>(finalPosition[1]), static_cast<float>(finalPosition[2]));

				if (mHasNormal)
				{
					pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, lCurrentNormal);
					fbxsdk::FbxVector4 finalNormal = TotalMatrixForNormal.MultT(lCurrentNormal);
					modelDesc.vecNormal[lVertexCount] = Vector3(static_cast<float>(finalNormal[0]), static_cast<float>(finalNormal[1]), static_cast<float>(finalNormal[2]));
				}

				if (mHasUV)
				{
					bool lUnmappedUV;
					pMesh->GetPolygonVertexUV(lPolygonIndex, lVerticeIndex, lUVName, lCurrentUV, lUnmappedUV);
					modelDesc.vecUV[lVertexCount] = Vector2(static_cast<float>(lCurrentUV[0]), static_cast<float>(lCurrentUV[1]));
				}
			}
			++lVertexCount;
		}
		modelDesc.vecSubMeshInfo[lMaterialIndex].nTriangleCount += 1;
	}

	//GetSmoothing(pMesh);

	return true;
}

void HrFBXLoader::GetSmoothing(fbxsdk::FbxMesh* pMesh)
{
	auto lMesh = pMesh;
	if (lMesh)
	{
		//if there's no smoothing info in fbx file, but you still want to get smoothing info.
		//please compute smoothing info from normals.
		//Another case to recompute smoothing info from normals is:
		//If users edit normals manually in 3ds Max or Maya and export the scene to FBX with smoothing info,
		//The smoothing info may NOT match with normals.
		//the mesh called "fbx_customNormals" in Normals.fbx is the case. All edges are hard, but normals actually represent the "soft" looking.
		//Generally, the normals in fbx file holds the smoothing result you'd like to get.
		//If you want to get correct smoothing info(smoothing group or hard/soft edges) which match with normals,
		//please drop the original smoothing info of fbx file, and recompute smoothing info from normals.
		//if you want to get soft/hard edge info, please call FbxGeometryConverter::ComputeEdgeSmoothingFromNormals().
		//if you want to get smoothing group info, please get soft/hard edge info first by ComputeEdgeSmoothingFromNormals() 
		//And then call FbxGeometryConverter::ComputePolygonSmoothingFromEdgeSmoothing().
		//if (pCompute)
		//{
		//	FbxGeometryConverter lGeometryConverter(pSdkManager);
		//	lGeometryConverter.ComputeEdgeSmoothingFromNormals(lMesh);
		//	//convert soft/hard edge info to smoothing group info
		//	if (pConvertToSmoothingGroup)
		//		lGeometryConverter.ComputePolygonSmoothingFromEdgeSmoothing(lMesh);
		//}

		//if there is smoothing groups info in your fbx file, but you want to get hard/soft edges info
		//please use following code:
		//FbxGeometryConverter lGeometryConverter(lSdkManager);
		//lGeometryConverter.ComputeEdgeSmoothingFromPolygonSmoothing(lMesh);

		//get smoothing info
		FbxGeometryElementSmoothing* lSmoothingElement = lMesh->GetElementSmoothing();
		if (lSmoothingElement)
		{
			//mapping mode is by edge. The mesh usually come from Maya, because Maya can set hard/soft edges.
			//we can get smoothing info(which edges are soft, which edges are hard) by retrieving each edge. 
			if (lSmoothingElement->GetMappingMode() == FbxGeometryElement::eByEdge)
			{
				//Let's get smoothing of each edge, since the mapping mode of smoothing element is by edge
				for (int lEdgeIndex = 0; lEdgeIndex < lMesh->GetMeshEdgeCount(); lEdgeIndex++)
				{
					int lSmoothingIndex = 0;
					//reference mode is direct, the smoothing index is same as edge index.
					//get smoothing by the index of edge
					if (lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						lSmoothingIndex = lEdgeIndex;

					//reference mode is index-to-direct, get smoothing by the index-to-direct
					if (lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						lSmoothingIndex = lSmoothingElement->GetIndexArray().GetAt(lEdgeIndex);

					//Got smoothing of each vertex.
					int lSmoothingFlag = lSmoothingElement->GetDirectArray().GetAt(lSmoothingIndex);
					//if (gVerbose) FBXSDK_printf("hard/soft value for edge[%d]: %d \n", lEdgeIndex, lSmoothingFlag);
					//add your custom code here, to output smoothing or get them into a list, such as KArrayTemplate<int>
					//. . .
				}//end for lEdgeIndex
			}//end eByEdge
			 //mapping mode is by polygon. The mesh usually come from 3ds Max, because 3ds Max can set smoothing groups for polygon.
			 //we can get smoothing info(smoothing group ID for each polygon) by retrieving each polygon. 
			else if (lSmoothingElement->GetMappingMode() == FbxGeometryElement::eByPolygon)
			{
				//Let's get smoothing of each polygon, since the mapping mode of smoothing element is by polygon.
				for (int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
				{
					int lSmoothingIndex = 0;
					//reference mode is direct, the smoothing index is same as polygon index.
					if (lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						lSmoothingIndex = lPolygonIndex;

					//reference mode is index-to-direct, get smoothing by the index-to-direct
					if (lSmoothingElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						lSmoothingIndex = lSmoothingElement->GetIndexArray().GetAt(lPolygonIndex);

					//Got smoothing of each polygon.
					int lSmoothingFlag = lSmoothingElement->GetDirectArray().GetAt(lSmoothingIndex);
					
					//if (gVerbose) FBXSDK_printf("smoothing group ID for polygon[%d]: %d \n", lPolygonIndex, lSmoothingFlag);
					//add your custom code here, to output normals or get them into a list, such as KArrayTemplate<int>
					//. . .

					//lMesh->GetElementSmoothing()

				}//end for lPolygonIndex //PolygonCount

			}//end eByPolygonVertex
		}//end if lSmoothingElement
	}//end if lMesh
}

