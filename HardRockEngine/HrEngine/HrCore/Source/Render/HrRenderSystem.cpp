#include "Render/HrRenderSystem.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"
#include "Render/HrViewPort.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrShadowMap.h"
#include "Render/HrCamera.h"
#include "Render/HrDepthStencil.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderProcessing.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrWindowModule.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"

using namespace Hr;

HrRenderSystem::HrRenderSystem()
{
	BuildRenderProcesses();
}

HrRenderSystem::~HrRenderSystem()
{
}

void HrRenderSystem::StartRenderProcess()
{
	for (auto& pRenderProcessing : m_lisRenderProcessing)
	{
		pRenderProcessing->Run();
	}
}

void HrRenderSystem::BuildRenderProcesses()
{
	m_lisRenderProcessing.push_back(HrMakeSharedPtr<HrForwardProcessing>());
}

void HrRenderSystem::AppendRenderProcess(EnumRenderProcessingType type)
{
}

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
HrForwardRenderSystem::HrForwardRenderSystem()
{

}

HrForwardRenderSystem::~HrForwardRenderSystem()
{

}

void HrForwardRenderSystem::BuildRenderProcesses()
{

}

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

HrDeferredRenderSystem::HrDeferredRenderSystem()
{

}

HrDeferredRenderSystem::~HrDeferredRenderSystem()
{

}

