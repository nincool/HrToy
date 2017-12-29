#ifndef _HR_SCENEOBJECTFACTORY_H_
#define _HR_SCENEOBJECTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
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

		HrCameraNodePtr CreateCamera();
		HrCameraNodePtr CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder);

		HrLightNodePtr CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular);

		//deprecated
		//HrLightNode* CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular);
		HrLightNode* CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2);
		
		HrSceneNode* CreatePlane(float fWidth, float fHeight);
		HrSceneNode* CreateBox(float fLength);
		HrSceneNode* CreateSkyBox();

		HrSceneNodePtr CreateModel(const std::string& strName);

		/**
		 @Comment: 创建场景节点 [12/29/2017 By Hr]
		 @Param: 场景资源
		 @Return: 场景节点对象
		*/
		HrSceneNodePtr CreateSceneNode(HrPrefabModelPtr& pPrefabModel);
	private:
		//资源模块加载
		HrGeometryFactoryPtr m_pGeometryFactory;
	};
}


#endif



