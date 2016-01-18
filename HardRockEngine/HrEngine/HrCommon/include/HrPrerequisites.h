#ifndef _HR_PREREQUISITES_H_
#define _HR_PREREQUISITES_H_

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <assert.h>
#include <memory>

#include "HrConfig.h"
#include "HrPlatformConfig.h"
#include "HrMacros.h"
#include "HrStringUtil.h"

namespace Hr
{
	class IRenderer;
	typedef std::shared_ptr<IRenderer> IRendererPrt;
	class HrD3D11Render;

	class ICamera;
	typedef std::shared_ptr<ICamera> ICameraPtr;
	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;


}

#endif




