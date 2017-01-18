#ifndef _HR_FBXLOADER_H_
#define _HR_FBXLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"

namespace fbxsdk
{
	class FbxManager;
	class FbxScene;
	class FbxDocument;
	class FbxNode;
	class FbxMesh;
	class FbxAMatrix;
}

namespace Hr
{
	class HrFBXLoader 
	{
	public:
		HrFBXLoader();
		~HrFBXLoader();

		void Load(std::string& strFile, HrModelDescInfo& modelDesc);

	private:
		void InitializeSDKObjects();
		void DestroySdkObjects(bool pExitStatus);

		bool LoadScene(const char* pFilename);

		void ParseFBXSdkScene(HrModelDescInfo& modelDesc);
		
		void ParseFBXSdkNode(fbxsdk::FbxNode* pNode, HrModelDescInfo& modelDesc);

		void ReadMesh(fbxsdk::FbxNode* pNode, HrModelDescInfo& modelDesc);

		/**
		* Compute the global matrix for Fbx Node
		*
		* @param Node	Fbx Node
		* @return KFbxXMatrix*	The global transform matrix
		*/
		fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* pNode);
		/**
		* Check if there are negative scale in the transform matrix and its number is odd.
		* @return bool True if there are negative scale and its number is 1 or 3.
		*/
		bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);

		void ReadVertexPos(fbxsdk::FbxMesh* pMesh, fbxsdk::FbxAMatrix& totalMatrix, HrModelDescInfo::HrSubMeshInfo& subMeshInfo);
		void ReadVertexNormal(fbxsdk::FbxMesh* pMesh, fbxsdk::FbxAMatrix& totalMatrixForNormal, HrModelDescInfo::HrSubMeshInfo& subMeshInfo);
		void ReadVertexColor(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo);
		void ReadVertexUV(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo);
		void ReadMaterial(fbxsdk::FbxMesh* pMesh, HrModelDescInfo::HrSubMeshInfo& subMeshInfo);
		void ReadMaterialConnections(fbxsdk::FbxMesh* pMesh);
		
		//void CalculateAverageNormals(HrModelDescInfo::HrMeshInfo& meshInfo);

		//void BuildSubMeshInfo(HrModelDescInfo::HrMeshInfo& modelDesc);
	private:
		fbxsdk::FbxManager* m_pFbxManager;
		fbxsdk::FbxScene* m_pScene;
	};
}


#endif



