#ifndef _HR_SCENEOBJECTFACTORY_H_
#define _HR_SCENEOBJECTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

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
		HrSceneNode* CreateBox();

	private:
		//资源模块加载
		HrGeometryFactoryPtr m_pGeometryFactory;
	};
}


#endif



