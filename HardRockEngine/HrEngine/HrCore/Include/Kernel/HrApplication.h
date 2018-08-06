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

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrApplication 
	{
	public:
		HrApplication();
		virtual ~HrApplication();

		enum class Platform
		{
			PLAT_OS_WINDOWS,/** Windows */
			PLAT_OS_LINUX,/** Linux */
			PLAT_OS_MAC,/** Mac*/
			PLAT_OS_ANDROID,/** Android */
			PLAT_OS_IPHONE,/** Iphone */
			PLAT_OS_IPAD,/** Ipad */
			PLAT_OS_BLACKBERRY,/** BLACKBERRY */
			PLAT_OS_NACL,/** Nacl */
			PLAT_OS_EMSCRIPTEN,/** Emscripten */
			PLAT_OS_TIZEN,/** Tizen */
			PLAT_OS_WINRT,/** Winrt */
			PLAT_OS_WP8/** WP8 */
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

		virtual void Run();

		virtual bool Destroy();
	};
}

#endif

