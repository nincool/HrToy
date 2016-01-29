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

		virtual bool Init() override;
		virtual void StartMainLoop() override;
		virtual void End() override;
		virtual void Release() override;

		virtual bool Render() override;
		

	private:
		static HrDirectorPtr m_s_pUniqueDirector;

		IRenderFactoryPtr m_pShareRenderFactory;
		IRenderPtr m_pShareRender;

		bool m_bEndMainLoop;

		std::unique_ptr<HrModuleLoader> m_pUniqueRenderLoader;

	};

}

#endif





