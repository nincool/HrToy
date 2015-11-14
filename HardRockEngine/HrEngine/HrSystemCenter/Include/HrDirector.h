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

#include "HrSystemCenterPrerequisites.h"
#include "IDirector.h"

namespace Hr
{
	class IRenderer;
	class HrSystemSupporter;

	class HrDirector : public IDirector
	{
	public:
		~HrDirector();

		virtual bool Init() override;
		virtual void Go() override;


		HR_INSTANCE(HrDirector);
	public:
		HR_SYNTHESIZE_READONLY(HrSystemSupporter*, m_pSystemSupporter, SystemSupporter);
	protected:
		HrDirector();

		bool LoadRenderSystem();
	private:
		HINSTANCE m_hHandleRender;
		IRenderer* m_pRenderSystem;
	};

}

#endif





