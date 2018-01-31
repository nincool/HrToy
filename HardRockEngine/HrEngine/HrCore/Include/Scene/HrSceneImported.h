#ifndef _HR_SCENEIMPORTED_H_
#define _HR_SCENEIMPORTED_H_

#include "HrCore/Include/Scene/HrScene.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

namespace Hr
{
	struct HrSceneInfo
	{
		enum EnumEntityType
		{
			ET_CAMERA = 0,
			ET_LIGHT,
			ET_PREFAB
		};

		//lights
		struct HrSceneLightInfo
		{
			int nLightType;
			std::string strLightName;
			Vector3 vPosition;
			Vector3 vDirection;
			HrColor diffuseColor;
			HrColor specularColor;
		};

		//Camera

		struct HrSceneNodeInfo
		{
			std::string strName;
			int nEnable;
			EnumEntityType nEntityType;
			std::string strEntityResource;
			Vector3 v3Position;
			Vector3 v3Rotation;
			Vector3 v3Scale;
			HrSceneLightInfo sceneLightInfo;
			std::vector<HrSceneNodeInfo> vecChildrenSceneNode;
		};
		
		HrColor ambientColor;

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
		void CreateSceneNode(const HrSceneNodePtr& pParent, const std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo);
	protected:
		HrSceneInfo m_sceneDataInfo;

		HrSceneNodePtr m_pSceneMainCamera;

	};
}

#endif




