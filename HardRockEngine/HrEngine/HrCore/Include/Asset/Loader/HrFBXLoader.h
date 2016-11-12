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
}

namespace Hr
{
	class HrFBXLoader 
	{
	public:
		HrFBXLoader();
		~HrFBXLoader();

		void Load(std::string& strFile, std::vector<Vertex>& vecVertex, std::vector<uint32>& vecIndexBuffer);

	private:
		void InitializeSDKObjects(fbxsdk::FbxManager*& pManager, fbxsdk::FbxScene*& pScene);
		void DestroySdkObjects(fbxsdk::FbxManager* pManager, bool pExitStatus);

		bool LoadScene(fbxsdk::FbxManager* pManager, fbxsdk::FbxDocument* pScene, const char* pFilename);

		void ParseFBXSdkScene(fbxsdk::FbxScene* pScene, std::vector<Vertex>& vecVertex, std::vector<uint32>& vecIndexBuffer);
		void ParseFBXSdkNode(fbxsdk::FbxNode* pNode, std::vector<Vertex>& vecVertex, std::vector<uint32>& vecIndexBuffer);

		void ReadMesh(fbxsdk::FbxNode* pNode, std::vector<Vertex>& vecVertex, std::vector<uint32>& vecIndexBuffer);

	private:
		std::vector<Vector3> m_vecVertexPosition;
		std::vector<uint32> m_vecIndexBuffer;
	};
}


#endif



