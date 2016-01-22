/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [10/28/2015 By Hr]
*
************************************************************************/


#ifndef _HR_IAPPLICATION_H_
#define _HR_IAPPLICATION_H_

#include "HrCore/Include/HrCorePreDeclare.h"
//#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IApplication //: public GeneralAllocatedObject
	{
	public:
		IApplication(){};
		virtual ~IApplication()
		{
		}

		enum class Platform
		{
			OS_WINDOWS,/** Windows */
			OS_LINUX,/** Linux */
			OS_MAC,/** Mac*/
			OS_ANDROID,/** Android */
			OS_IPHONE,/** Iphone */
			OS_IPAD,/** Ipad */
			OS_BLACKBERRY,/** BLACKBERRY */
			OS_NACL,/** Nacl */
			OS_EMSCRIPTEN,/** Emscripten */
			OS_TIZEN,/** Tizen */
			OS_WINRT,/** Winrt */
			OS_WP8/** WP8 */
		};

		/**
		* @brief    Implement Director and Scene init code here.
		* @return true    Initialize success, app continue.
		* @return false   Initialize failed, app terminate.
		*/
		virtual bool ApplicationDidFinishLaunching() = 0;

		/**
		* @brief  This function will be called when the application enters background.
		*/
		virtual void ApplicationDidEnterBackground() = 0;

		/**
		* @brief  This function will be called when the application enters foreground.
		*/
		virtual void ApplicationWillEnterForeground() = 0;

		/**
		@brief Get target platform.
		*/
		virtual Platform GetTargetPlatform() = 0;

		virtual void Run() = 0;

		virtual bool Destroy() = 0;
	};
}

#endif

