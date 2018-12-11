#include "Render/HrRenderProcessing.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrRenderModule.h"

using namespace Hr;

HrRenderProcessing::HrRenderProcessing()
{
}

HrRenderProcessing::~HrRenderProcessing()
{
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrForwardProcessing::HrForwardProcessing()
{

}

HrForwardProcessing::~HrForwardProcessing()
{

}

void HrForwardProcessing::Run()
{
	auto& pRenderModuel = HrDirector::Instance()->GetRenderModule();
	auto& pSceneModel = HrDirector::Instance()->GetSceneModule();

	pRenderModuel->BindFrameBuffer(nullptr);
	pRenderModuel->ClearRenderFame();
	pSceneModel->RenderVisibleObjects();
	pRenderModuel->Present();
}

