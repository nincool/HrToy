#include "HrCore/Include/Kernel/HrModule.h"
#include "HrCore/Include/Kernel/HrLog.h"

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"

using namespace Hr;

HrModule::HrModule()
{

}

HrModule::~HrModule()
{

}

bool HrModule::InitComponent()
{
	return true;
}

bool HrModule::Update(float fDelta)
{
	return true;
}



