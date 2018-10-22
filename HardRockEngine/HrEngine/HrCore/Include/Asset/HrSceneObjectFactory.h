#ifndef _HR_SCENEOBJECTFACTORY_H_
#define _HR_SCENEOBJECTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"
#include "HrCommon/include/HrSingleton.h"
#include "HrMath/Include/HrMath.h"


namespace Hr
{
	class HrModuleLoader;

	class HR_CORE_API HrSceneObjectFactory : public HrSingleTon<HrSceneObjectFactory>
	{
	public:
		HrSceneObjectFactory();
		~HrSceneObjectFactory();

		/**
		 @Comment: 创建场景摄像机 [1/8/2018 By Hr]
		 @Param:   视口参数
		 @Return:  摄像机节点
		*/
		HrSceneNodePtr CreateCamera(const std::string& strName);
		HrSceneNodePtr CreateCamera(const std::string& strName, float nTopX, float nTopY, float nWidth, float nHeight, int nZOrder);

		/**
		 @Comment: 创建Pefab配置文件模型节点 [3/27/2018 By Hr]
		 @Param:
		 @Return:
		*/
		HrSceneNodePtr CreateModelNode(const std::string& strName);
		/**
		 @Comment: 创建场景节点 [12/29/2017 By Hr]
		 @Param:   场景资源
		 @Return:  场景节点对象
		*/
		HrSceneNodePtr CreateSceneNode(HrModelPtr& pModel);

		HrSceneNodePtr CreateMeshModelNode(HrMeshModelPtr& pMeshModel);


		/**
		 @Comment: 创建灯光 [3/7/2018 By Hr]
		 @Param:   lightType 灯光类型
		 @Return:  灯光场景节点
		*/
		HrSceneNodePtr CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType);


		/////////////////////////////////////////////////////////
		//
		/////////////////////////////////////////////////////////
		HrSceneNodePtr CreateGridPlan();


		HrSceneNodePtr CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight);

	private:
		HrSceneNodePtr CreateSceneNode(const std::string& strName);
	};
}


#endif



