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
	class FbxAnimLayer;
	class FbxTime;
	class FbxPose;
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
		bool IsOddNegativeScale(fbxsdk::FbxAMatrix& TotalMatrix);

		bool IsAllIndices(HrModelDescInfo::HrSubMeshInfo& meshInfo);

		void LoadCacheRecursive(fbxsdk::FbxScene * pScene, fbxsdk::FbxAnimLayer * pAnimLayer, const char * pFbxFileName, bool pSupportVBO, HrModelDescInfo& modelDesc);
		void LoadCacheRecursive(fbxsdk::FbxNode * pNode, fbxsdk::FbxAnimLayer * pAnimLayer, bool pSupportVBO, HrModelDescInfo& modelDesc);
		bool InitializeSubMesh(fbxsdk::FbxMesh* pMesh, HrModelDescInfo& modelDesc);

		//get mesh smoothing info
		//set pCompute true to compute smoothing from normals by default 
		//set pConvertToSmoothingGroup true to convert hard/soft edge info to smoothing group info by default
		void GetSmoothing(fbxsdk::FbxMesh* pMesh);

		fbxsdk::FbxAMatrix GetGlobalPosition(fbxsdk::FbxNode* pNode, const fbxsdk::FbxTime& pTime, fbxsdk::FbxPose* pPose = NULL, fbxsdk::FbxAMatrix* pParentGlobalPosition = NULL);
		fbxsdk::FbxAMatrix GetPoseMatrix(fbxsdk::FbxPose* pPose, int pNodeIndex);
	private:
		fbxsdk::FbxManager* m_pFbxManager;
		fbxsdk::FbxScene* m_pScene;
		fbxsdk::FbxAnimLayer * m_pCurrentAnimLayer;

		std::unordered_map<int, int> m_mapIndexCached;

		bool mHasNormal = false;
		bool mHasUV = false;
		bool mAllByControlPoint = false;

		const int TRIANGLE_VERTEX_COUNT = 3;

		// Four floats for every position.
		const int VERTEX_STRIDE = 3;
		// Three floats for every normal.
		const int NORMAL_STRIDE = 3;
		// Two floats for every UV.
		const int UV_STRIDE = 2;
	};
}


#endif



