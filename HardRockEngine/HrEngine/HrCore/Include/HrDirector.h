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

#include "IDirector.h"
#include <boost/noncopyable.hpp>

namespace Hr
{
	class ITimer;
	class HrModuleLoader;

	class HR_CORE_API HrDirector : public IDirector, public boost::noncopyable
	{
	public:
		HrDirector();
		~HrDirector();

		static HrDirector& GetInstance();
		static void ReleaseInstance();

		/////////////////////////////--- 生命周期 ---/////////////////////////////////
		virtual bool Init() override;
		virtual void StartMainLoop() override;
		virtual void End() override;
		virtual void Release() override;

		/////////////////////////////--- 渲染 ---/////////////////////////////////
		virtual bool Render() override;

		/////////////////////////////--- 业务 ---/////////////////////////////////
		virtual void RunScene(const IScenePtr& pScene);

	protected:
		void Update();
	private:
		static HrDirectorPtr m_s_pUniqueDirector;
		//场景管理器
		ISceneManagerPtr m_pShareSceneManager;
		//渲染工厂
		IRenderFactoryPtr m_pShareRenderFactory;
		//渲染器
		IRenderPtr m_pShareRender;

		bool m_bEndMainLoop;

		//渲染模块加载
		std::unique_ptr<HrModuleLoader> m_pUniqueRenderLoader;

	};

}

#endif





