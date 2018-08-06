#include "HrMeshConvertCore.h"
#include "HrCore/Include/Kernel/HrDirector.h"

using namespace Hr;


HrMeshConvertCore::HrMeshConvertCore(void* pWnd)
{
	m_pWnd = pWnd;
}

HrMeshConvertCore::~HrMeshConvertCore()
{

}

void HrMeshConvertCore::Run()
{
	if (!HrDirector::Instance()->Init(m_pWnd))
	{
		throw std::runtime_error("error");
	}
	else
	{
		ApplicationDidFinishLaunching();
	}
}
