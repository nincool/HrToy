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

		HrCameraNode* CreateCamera();
		HrCameraNode* CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder);

		HrLightNode* CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular);
		HrLightNode* CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2);
		
		HrSceneNode* CreatePlane(float fWidth, float fHeight);
		HrSceneNode* CreateBox(float fLength);
		HrSceneNode* CreateSkyBox();

		HrSceneNode* CreateModel(const std::string& strName);

	private:
		//��Դģ�����
		HrGeometryFactoryPtr m_pGeometryFactory;
	};
}


#endif



