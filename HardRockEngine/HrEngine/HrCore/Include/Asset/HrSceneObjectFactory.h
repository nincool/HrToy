#ifndef _HR_SCENEOBJECTFACTORY_H_
#define _HR_SCENEOBJECTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"
#include "HrCommon/include/HrSingleton.h"
#include "HrMath/Include/HrMath.h"
#include "HrCore/Include/Render/HrCamera.h"

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
		HrSceneNodePtr CreateCamera(const std::string& strName, HrCamera::EnumCameraType cameraType = HrCamera::CT_PERSPECTIVE);
		HrSceneNodePtr CreateCamera(const std::string& strName, HrCamera::EnumCameraType cameraType, float nTopX, float nTopY, float nWidth, float nHeight, int nZOrder);

		/**
		 @Comment: ����Pefab�����ļ�ģ�ͽڵ� [3/27/2018 By Hr]
		 @Param:
		 @Return:
		*/
		HrSceneNodePtr CreateModelNode(const std::string& strName);

		/**
		 @Comment: ����Scene�ڵ� [10/30/2018 By Hr]
		 @Param: HrMeshModelPtr 
		 @Return: HrSceneNodePtr
		*/
		HrSceneNodePtr CreateMeshModelNode(HrMeshModelPtr& pMeshModel);


		/**
		 @Comment: �����ƹ� [3/7/2018 By Hr]
		 @Param:   lightType �ƹ�����
		 @Return:  �ƹⳡ���ڵ�
		*/
		HrSceneNodePtr CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType);

		/**
		 @Comment: ������պнڵ� [4/3/2019 By Hr]
		 @Param:
		 @Return:
		*/
		HrSceneNodePtr CreateSkyBoxNode(const std::string& strName, const HrTexturePtr& pCubeMap);
		/////////////////////////////////////////////////////////
		//
		/////////////////////////////////////////////////////////
		HrSceneNodePtr CreateGridPlan();


		HrSceneNodePtr CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight);
		HrSceneNodePtr CreateQuadNodePN(const std::string& strName, float fWidth, float fHeight);

		/**
		 @Comment: �������� [3/23/2019 By Hr]
		 @Param: fRadius �뾶 fSlice ����ʱ���п� fStack ƽ��ʱ���п�
		 @Return:
		*/
		HrSceneNodePtr CreateSphereNode(const std::string& strName, float fRadius, int fSlice, int fStack);

		/////////////////////////////////////////////////////////
		
	private:
		HrSceneNodePtr CreateSceneNode(const std::string& strName);
		HrSceneNodePtr BuildupSceneNodeWithMesh(const HrMeshModelPtr& pMeshModel, const HrSceneNodePtr& pSceneNode);
	};
}


#endif



