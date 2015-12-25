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

namespace Hr
{
	class IRenderer;
	class ITimer;

	class HrSystemSupporter;

	class HR_MAIN_API HrDirector : public IDirector
	{
	public:
		~HrDirector();

		virtual bool Init() override;
		virtual void StartMainLoop() override;
		virtual void End() override;
		virtual void Release() override;

		virtual bool Render() override;
		

		HR_INSTANCE(HrDirector);
	public:
		HR_SYNTHESIZE_READONLY(HrSystemSupporter*, m_pSystemSupporter, SystemSupporter);
	protected:
		HrDirector();

		bool LoadRenderSystem();

	private:
		HINSTANCE m_hHandleRender;
		IRenderer* m_pRenderSystem;

		bool m_bEndMainLoop;

		ITimer* m_pTimer;
	};

}

#endif





