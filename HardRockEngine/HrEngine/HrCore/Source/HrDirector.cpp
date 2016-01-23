#include "HrDirector.h"
#include "HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrModuleLoader.h"


//#include "HrSceneManager.h"
//#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
//#include "HrWin32WindowEventUtilities.h"
//#include "HrSystemSupporter.h"
//#include "HrLog.h"
//#include "HrTimer.h"

using namespace Hr;

HrDirectorPtr HrDirector::m_s_pUniqueDirector;

HrDirector& HrDirector::GetInstance()
{
	if (!m_s_pUniqueDirector)
	{
		m_s_pUniqueDirector = MakeUniquePtr<HrDirector>();
	}
	return *m_s_pUniqueDirector;
}

void HrDirector::ReleaseInstance()
{
	if (m_s_pUniqueDirector)
	{
		m_s_pUniqueDirector->Release();
	}
	m_s_pUniqueDirector.reset();
}

HrDirector::HrDirector()
{
	m_bEndMainLoop = false;
}

HrDirector::~HrDirector()
{
}

bool HrDirector::Init()
{
	HRLOG(_T("HrDirector Init!"));


	//m_pUniqueModuleLoader = MakeUniquePtr<HrModuleLoader>("HrRenderD3D11", "HrModuleInitialize");
	//m_pUniqueModuleLoader->HrLoadModule();
	//typedef void(*RenderInitFunc)(IRenderPtr& ptr);
	//RenderInitFunc func= static_cast<RenderInitFunc>(m_pUniqueModuleLoader->GetProcAddress());
	//if (func)
	//{
	//	func(m_pShareRender);
	//}
	//else
	//{

	//}

	//m_pShareSceneManager = make_shared<HrSceneManager>();

	//if (!LoadRenderSystem())
	//{
	//	HRERROR(_T("Director Init : LoadRenderSystem Error!"));
	//	return false;
	//}
	
	return true;
}

void HrDirector::StartMainLoop()
{
	while (!m_bEndMainLoop)
	{
#if HR_TARGET_PLATFORM == HR_PLATFORM_WIN32
		//if (!HrWin32WindowEventUtilities::MessagePump())
		//{
		//	break;
		//}
#endif
		//m_pTimer->Tick();
		Render();
	}
}

void HrDirector::End()
{
	m_bEndMainLoop = true;
}

void HrDirector::Release()
{
	//m_pShareRenderSystem->Release();
	//typedef void(*RENDER_END_FUNC)();
	//if (m_hHandleRender != nullptr)
	//{
	//	RENDER_END_FUNC pFuncEnd = (RENDER_END_FUNC)HR_MODULE_GETSYSTEM(m_hHandleRender, HR_MUDULE_END_FUNC);
	//	if (pFuncEnd != nullptr)
	//	{
	//		pFuncEnd();
	//	}
	//	m_pShareRenderSystem.reset();
	//	HR_MODULE_FREE(m_hHandleRender);
	//}
}

bool HrDirector::Render()
{
	return true;
}


