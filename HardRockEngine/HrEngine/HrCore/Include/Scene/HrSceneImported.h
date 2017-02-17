#ifndef _HR_SCENEIMPORTED_H_
#define _HR_SCENEIMPORTED_H_

#include "HrCore/Include/Scene/HrScene.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

namespace Hr
{
	struct HrSceneInfo
	{
		//lights
		//Camera
		struct HrSceneNodeInfo
		{
			std::string strName;
			std::string strEntityResource;
			Vector3 v3Position;
			Vector3 v3Rotation;
			Vector3 v3Scale;
			std::vector<HrSceneNodeInfo> vecChildrenSceneNode;
		};

		std::vector<HrSceneNodeInfo> vecSceneNodeInfo;
	};

	class HR_CORE_API HrSceneImported : public HrScene
	{
	public:
		HrSceneImported();
		~HrSceneImported();

		bool LoadScene(const std::string& strSceneName);

	protected:
		void LoadSceneNode(const rapidjson::Value& jsonValue, std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo);

		virtual void CreateSceneFromData();
		void CreateSceneNode(HrSceneNode* pParent, std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo);
	protected:
		HrSceneInfo m_sceneDataInfo;

		HrCameraNode* m_pSceneMainCamera;

	};
}

#endif




