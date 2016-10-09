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

		//IRenderPtr& GetRenderer()
		//{
		//	return m_pShareRender;
		//}
		
		HrRenderFactoryPtr& GetRenderFactory()
		{
			return m_pShareRenderFactory;
		}
		
		//const IRenderTargetPtr& GetRenderTarget()
		//{
		//	return m_pShareRenderTarget;
		//}
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
		void Update();
	private:
		//渲染目标
		//IRenderTargetPtr m_pShareRenderTarget;
		//场景管理器
		HrSceneManagerPtr m_pShareSceneManager;
		//渲染工厂
		HrRenderFactoryPtr m_pShareRenderFactory;
		
		//渲染器
		HrRenderPtr m_pShareRender;

		bool m_bEndMainLoop;

		//渲染模块加载
		std::unique_ptr<HrModuleLoader> m_pUniqueRenderLoader;
	};

}

#endif





