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

	class HR_CORE_API HrDirector : public HrSingleTon<HrDirector>, public boost::noncopyable
	{
	public:
		HrDirector();
		~HrDirector();


		const HrSchedulerPtr& GetScheduler()
		{
			return m_pScheduler;
		}

		const HrCoreComponentEventPtr& GetEventComponent();
		const HrCoreComponentWinPtr& GetWinCoreComponent();
		const HrCoreComponentRenderPtr& GetRenderCoreComponent();
		const HrCoreComponentScenePtr& GetSceneCoreComponent();


		/////////////////////////////--- 生命周期 ---/////////////////////////////////
		virtual bool Init();
		virtual void StartMainLoop();
		virtual void End();
		virtual void Destroy();

		/////////////////////////////--- 渲染 ---/////////////////////////////////
		virtual bool Render();

		/////////////////////////////--- 业务 ---/////////////////////////////////
		void Schedule(const std::function<void(float)>& callBack, void* pTarget, const std::string& strKey, float fInterval, uint32 nRepeat, float fDelay);
		void UnSchedule(size_t nTargetHashKeyID, size_t nHashID);

	protected:
		void CreateEventComponent();
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
		HrSchedulerPtr m_pScheduler;

		bool m_bEndMainLoop;

		/* delta time since last tick to main loop */
		float m_fDeltaTime;
		/* last time the main loop was updated */
		std::chrono::steady_clock::time_point m_lastUpdate;
		
		//渲染模块加载
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;

		HrCoreComponentEventPtr m_pEventComponent;
		HrCoreComponentWinPtr m_pWindowComponet;
		HrCoreComponentRenderPtr m_pRenderComponent;
		HrCoreComponentScenePtr m_pSceneManagerComponent;

	};

}

#endif





