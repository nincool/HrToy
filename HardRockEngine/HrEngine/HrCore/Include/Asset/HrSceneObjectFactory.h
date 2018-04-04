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
		 @Comment: ������������� [1/8/2018 By Hr]
		 @Param:   �ӿڲ���
		 @Return:  ������ڵ�
		*/
		HrSceneNodePtr CreateCamera(const std::string& strName, float nTopX, float nTopY, float nWidth, float nHeight, int nZOrder);

		//HrLightNodePtr CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular);

		//deprecated
		//HrLightNode* CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular);
		//HrLightNode* CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2);
		
		//HrSceneNodePtr CreatePlane(float fWidth, float fHeight);
		//HrSceneNode* CreateBox(float fLength);
		//HrSceneNode* CreateSkyBox();

		/**
		 @Comment: ����Pefab�����ļ�ģ�ͽڵ� [3/27/2018 By Hr]
		 @Param:
		 @Return:
		*/
		HrSceneNodePtr CreateModelNode(const std::string& strName);
		/**
		 @Comment: ���������ڵ� [12/29/2017 By Hr]
		 @Param:   ������Դ
		 @Return:  �����ڵ����
		*/
		HrSceneNodePtr CreateSceneNode(HrModelPtr& pModel);

		/**
		 @Comment: �����ƹ� [3/7/2018 By Hr]
		 @Param:   lightType �ƹ�����
		 @Return:  �ƹⳡ���ڵ�
		*/
		HrSceneNodePtr CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType);
	private:
		//HrGeometryFactoryPtr m_pGeometryFactory;
	};
}


#endif



