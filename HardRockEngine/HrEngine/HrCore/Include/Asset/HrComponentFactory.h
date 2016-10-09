#ifndef _HR_COMPONENTFACTORY_H_
#define _HR_COMPONENTFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrComponentFactory
	{
	public:
		HrComponentFactory();
		~HrComponentFactory();

		static HrComponentFactory& GetInstance();
		static void ReleaseInstance();

		static HrCameraNode* CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder);
	private:
		static HrComponentFactoryPtr m_s_pUniqueFactory;
	};
}

#endif



