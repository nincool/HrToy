/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_RENDERDEMOPREREQUISITES_H_
#define _HR_RENDERDEMOPREREQUISITES_H_

#ifdef HR_RENDERDEMO_EXPORT
#define HR_RENDERDEMO_API HR_EXPORT
#else
#define HR_RENDERDEMO_API HR_IMPORT
#endif // HR_MAIN_EXPORT

#include "../HrCommon/Include/HrPrerequisite.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "HrCore/Include/HrLog.h"
#include "HrCore/Include/HrCorePreDeclare.h"


#endif


