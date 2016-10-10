/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_DIRECTOR_H_
#define _HR_DIRECTOR_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class ITimer;
	class HrModuleLoader;

	class HR_CORE_API HrDirector : public HrSingleTon<HrDirector>
	{
	public:
		HrDirector();
		~HrDirector();


		HrRenderFactoryPtr& GetRenderFactory()
		{
			return m_pRenderFactory;
		}

		HrRenderPtr& GetRenderEngine()
		{
			return m_pRenderEngine;
		}

		const HrRenderTargetPtr& GetRenderTarget()
		{
			return m_pRenderTarget;
		}

		HrWindowPtr& GetWindow()
		{
			return m_pWindow;
		}

		/////////////////////////////--- 生命周期 ---/////////////////////////////////
		virtual bool Init();
		virtual void StartMainLoop();
		virtual void End();
		virtual void Release();

		/////////////////////////////--- 渲染 ---/////////////////////////////////
		virtual bool Render();

		/////////////////////////////--- 业务 ---/////////////////////////////////
		virtual void RunScene(const HrScenePtr& pScene);

	protected:
		bool CreateAppWindow();
		bool CreateRenderEngine();
		bool CreateRenderTarget();

		void Update();
	private:
		HrWindowPtr m_pWindow;

		//渲染目标
		HrRenderTargetPtr m_pRenderTarget;
		
		//场景管理器
		HrSceneManagerPtr m_pSceneManager;
		
		//渲染工厂
		HrRenderFactoryPtr m_pRenderFactory;
		
		//渲染器
		HrRenderPtr m_pRenderEngine;

		bool m_bEndMainLoop;

		//渲染模块加载
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;
	};

}

#endif





