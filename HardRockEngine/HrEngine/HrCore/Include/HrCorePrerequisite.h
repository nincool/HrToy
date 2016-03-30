/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/27/2015 By Hr]
*
************************************************************************/
#ifndef _HR_APPLICATIONPREREQUISITE_H_
#define _HR_APPLICATIONPREREQUISITE_H_

#include "HrCommon/Include/HrPrerequisite.h"
#include "HrCore/Include/HrCorePreDeclare.h"
#include "HrRenderSystem/HrRenderCommon/HrRenderPreDeclare.h"
#include "HrMath/Include/HrMath.h"

#ifdef HR_CORE_EXPORT
#define HR_CORE_API HR_EXPORT
#else
#define HR_CORE_API HR_IMPORT
#endif

#endif


