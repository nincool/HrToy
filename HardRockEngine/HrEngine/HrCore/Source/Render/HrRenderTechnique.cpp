#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"

using namespace Hr;

HrRenderTechnique::HrRenderTechnique()
{
	m_pRenderPass = nullptr;
}

HrRenderPass* HrRenderTechnique::GetRenderPass()
{
	return m_pRenderPass;
}

