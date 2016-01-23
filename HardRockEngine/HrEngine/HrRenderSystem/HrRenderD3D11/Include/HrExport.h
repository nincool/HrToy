/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/27/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_EXPORT_H_
#define _HR_EXPORT_H_

#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderCommon/HrRenderPreDeclare.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"

extern "C" HR_EXPORT void HrModuleInitialize(Hr::IRenderPtr& ptr);

extern "C" HR_EXPORT void HrModuleUnload(void);

#endif



