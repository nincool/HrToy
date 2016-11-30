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
}

namespace Hr
{
	class HrFBXLoader 
	{
	public:
		HrFBXLoader();
		~HrFBXLoader();

		void Load(std::string& strFile
			, std::string& strMeshName
			, std::vector<Vector3>& vecPrimaryPos
			, std::vector<Vector3>& vecVertexPos
			, std::vector<uint32>& vecIndice
			, std::vector<Vector3>& vecNormal);

	private:
		void InitializeSDKObjects(fbxsdk::FbxManager*& pManager, fbxsdk::FbxScene*& pScene);
		void DestroySdkObjects(fbxsdk::FbxManager* pManager, bool pExitStatus);

		bool LoadScene(fbxsdk::FbxManager* pManager, fbxsdk::FbxDocument* pScene, const char* pFilename);

		void ParseFBXSdkScene(fbxsdk::FbxScene* pScene
			, std::string& strMeshName
			, std::vector<Vector3>& vecPrimaryPos
			, std::vector<Vector3>& vecVertexPos
			, std::vector<uint32>& vecIndice
			, std::vector<Vector3>& vecNormal);
		
		void ParseFBXSdkNode(fbxsdk::FbxNode* pNode
			, std::string& strMeshName
			, std::vector<Vector3>& vecPrimaryPos
			, std::vector<Vector3>& vecVertexPos
			, std::vector<uint32>& vecIndice
			, std::vector<Vector3>& vecNormal);

		void ReadMesh(fbxsdk::FbxNode* pNode, std::string& strMeshName
			, std::vector<Vector3>& vecPrimaryPos
			, std::vector<Vector3>& vecVertexPos
			, std::vector<uint32>& vecIndice
			, std::vector<Vector3>& vecNormal);

		void ReadVertexPos(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecPrimaryPosition, std::vector<Vector3>& vecVertexPosition);
		void ReadIndice(fbxsdk::FbxMesh* pMesh, std::vector<uint32>& vecIndices);
		void ReadVertexNormal(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecVertexNormal);
	private:
	};
}


#endif



