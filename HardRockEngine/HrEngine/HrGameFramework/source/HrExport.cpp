#include "HrExport.h"
#include "HrGameFramework.h"

using namespace Hr;

extern "C" HR_EXPORT  void HrModuleInitialize() throw()
{
	IGameFramework* pGameFramework = HrGameFramework::GetInstance();
	if (pGameFramework != nullptr)
	{
		pGameFramework->Init();
	}
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{

}

