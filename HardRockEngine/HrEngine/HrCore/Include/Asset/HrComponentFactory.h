#ifndef _HR_COMPONENTFACTORY_H_
#define _HR_COMPONENTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrModuleLoader;

	class HR_CORE_API HrComponentFactory
	{
	public:
		HrComponentFactory();
		~HrComponentFactory();

		HrCameraNode* CreateCamera();
		HrCameraNode* CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder);
		HrSceneNode* CreateBox();

	private:
		//资源模块加载
		std::unique_ptr<HrModuleLoader> m_pAssetModuleLoader;
		HrAssetSystemFactoryPtr m_pAssetSystemFactory;
		HrGeometryFactoryPtr m_pGeometryFactory;
	};
}


#endif



