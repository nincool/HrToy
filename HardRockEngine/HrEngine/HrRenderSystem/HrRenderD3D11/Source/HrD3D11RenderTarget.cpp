#include "HrD3D11RenderTarget.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrWindowModule.h"
#include "HrCore/Include/Kernel/HrRenderModule.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11Texture.h"

using namespace Hr;

HrD3D11RenderTarget::HrD3D11RenderTarget(const HrTexturePtr& pTexture)
{
	HrD3D11Texture2DPtr pTexture2D = HrCheckPointerCast<HrD3D11Texture2D>(pTexture);
	CreateRenderTargetView(pTexture2D->GetD3D11Texture());
}

HrD3D11RenderTarget::HrD3D11RenderTarget(const ID3D11Texture2DPtr& pBackBuffer)
{
	CreateRenderTargetView(pBackBuffer);
}

void HrD3D11RenderTarget::CreateRenderTargetView(const ID3D11Texture2DPtr& pBackBuffer)
{
	m_pTexRenderTargetView = HrMakeSharedPtr<HrD3D11Texture2D>(pBackBuffer, HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW);
}

const ID3D11RenderTargetViewPtr& HrD3D11RenderTarget::GetRenderTargetView()
{
	BOOST_ASSERT(m_pTexRenderTargetView);
	return m_pTexRenderTargetView->GetD3DRenderTargetView();
}

