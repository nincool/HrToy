#include "HrD3D11BlendState.h"
#include "HrD3D11Render.h"

#include <boost/cast.hpp>

using namespace Hr;

HrD3D11BlendState::HrD3D11BlendState(ID3D11Device* pD3D11Device
	, ID3D11DeviceContext* pContext) :
	m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext)
{
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	TIF(m_pD3D11Device->CreateBlendState(&blendDesc, &m_pD3D11BlendState));
}

HrD3D11BlendState::~HrD3D11BlendState()
{

}

void HrD3D11BlendState::Bind(HrRender* pRender)
{
	HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11ImmediateContext();

	float blendFactor[4] = { 0.f,0.f,0.f,0.f };
	//开启“透明”效果
	pD3D11ImmediateContext->OMSetBlendState(m_pD3D11BlendState, blendFactor, 0xffffffff);
}
