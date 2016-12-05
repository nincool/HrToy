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

		void Load(std::string& strFile, HrModelDescInfo& modelDesc);

	private:
		void InitializeSDKObjects(fbxsdk::FbxManager*& pManager, fbxsdk::FbxScene*& pScene);
		void DestroySdkObjects(fbxsdk::FbxManager* pManager, bool pExitStatus);

		bool LoadScene(fbxsdk::FbxManager* pManager, fbxsdk::FbxDocument* pScene, const char* pFilename);

		void ParseFBXSdkScene(fbxsdk::FbxScene* pScene, HrModelDescInfo& modelDesc);
		
		void ParseFBXSdkNode(fbxsdk::FbxNode* pNode, HrModelDescInfo& modelDesc);

		void ReadMesh(fbxsdk::FbxNode* pNode, HrModelDescInfo& modelDesc);

		void ReadVertexPos(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecPrimaryPosition, std::vector<Vector3>& vecVertexPosition);
		void ReadIndice(fbxsdk::FbxMesh* pMesh, std::vector<uint16>& vecIndices);
		void ReadVertexNormal(fbxsdk::FbxMesh* pMesh, std::vector<Vector3>& vecVertexNormal);
		void ReadColor(fbxsdk::FbxMesh* pMesh, std::vector<float4>& vecColor);
		void ReadMaterialMapping(fbxsdk::FbxMesh* pMesh);
		void ReadMaterial(fbxsdk::FbxMesh* pMesh, std::vector<HrModelDescInfo::HrMaterialInfo>& vecMaterialInfo);
		void ReadMaterialConnections(fbxsdk::FbxMesh* pMesh, std::vector< std::vector<uint32> >& vecMaterialConnectInfo);
	private:
	};
}


#endif



