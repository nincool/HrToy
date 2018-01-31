#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderTarget.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrCoreComponentWin.h"
#include "HrCore/Include/Kernel/HrCoreComponentRender.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11Texture.h"

using namespace Hr;

HrD3D11RenderTarget::HrD3D11RenderTarget(const ID3D11Texture2DPtr& pBackBuffer)
{
	CreateRenderTargetView(pBackBuffer);
}

void HrD3D11RenderTarget::CreateRenderTargetView(const ID3D11Texture2DPtr& pBackBuffer)
{
	m_pTexRenderTargetView = HrMakeSharedPtr<HrD3D11Texture2D>(pBackBuffer, HrD3D11Texture::D3D_TEX_RENDERTARGETVIEW);
}

const ID3D11RenderTargetViewPtr& HrD3D11RenderTarget::GetRenderTargetView()
{
	BOOST_ASSERT(m_pTexRenderTargetView);
	return m_pTexRenderTargetView->GetD3DRenderTargetView();
}
