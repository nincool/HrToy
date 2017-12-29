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
#include <chrono>

namespace Hr
{
	class HrModuleLoader;

	class HR_CORE_API HrDirector : public HrSingleTon<HrDirector>
	{
	public:
		HrDirector();
		~HrDirector();


		const HrSchedulerPtr& GetScheduler()
		{
			return m_pScheduler;
		}


		const HrWinCoreComponentPtr& GetWinCoreComponent();
		const HrRenderCoreComponentPtr& GetRenderCoreComponent();
		const HrSceneCoreComponentPtr& GetSceneComponent();


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

		void CreateWindowComponent();
		void CreateSceneComponent();
		void CreateRenderComponent();
		


		bool CreateRenderState();
		void ReleaseRenderState();

		bool CreateResourceManager();
		void ReleaseResourceManager();

		bool CreateInputManager();
		void ReleaseInputManager();


		void Update();

	private:
		void CalculateDeltaTime();
	private:
		HrWindowPtr m_pWindow;
		
		//渲染工厂
		//HrRenderFactoryPtr m_pRenderFactory;
		//渲染器
		//HrRenderPtr m_pRenderEngine;
		//渲染目标
		HrRenderTargetPtr m_pRenderTarget;		
		//场景管理器
		//HrSceneManagerPtr m_pSceneManager;

		HrSchedulerPtr m_pScheduler;

		bool m_bEndMainLoop;

		/* delta time since last tick to main loop */
		float m_fDeltaTime;
		/* last time the main loop was updated */
		std::chrono::steady_clock::time_point m_lastUpdate;
		
		//渲染模块加载
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;


		HrWinCoreComponentPtr m_pWindowComponet;
		HrRenderCoreComponentPtr m_pRenderComponent;
		HrSceneCoreComponentPtr m_pSceneManagerComponent;
	};

}

#endif





