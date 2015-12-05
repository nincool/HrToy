/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/28/2015 By Hr]
*
************************************************************************/  

#ifndef _I_RENDERER_H_
#define _I_RENDERER_H_

#include "../../HrCommon/Include/HrPlatformConfig.h"

namespace Hr
{
	class IDirector;

	class IRenderer
	{
	public:
		virtual ~IRenderer(){};
		/**
		 *	@Brief:  创建渲染器[10/28/2015 By Hr]
		 *	@Param:
		 *	@Return:
		*/
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) = 0;
#else
		virtual bool Init(unsigned int nWidth, unsigned int nHeight) = 0;
#endif
		
		/**
		*	@Brief:  摧毁渲染器[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
		virtual void Release() = 0;
	};
}


#endif


