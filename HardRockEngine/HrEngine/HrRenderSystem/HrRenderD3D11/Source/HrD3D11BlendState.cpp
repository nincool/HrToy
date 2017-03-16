#include "HrD3D11BlendState.h"
#include "HrD3D11Render.h"
#include "HrD3D11Mapping.h"

#include <boost/cast.hpp>

using namespace Hr;

HrD3D11BlendState::HrD3D11BlendState(ID3D11Device* pD3D11Device
	, ID3D11DeviceContext* pContext
	, const HrBlendState::HrBlendStateDesc& blendDesc):
	m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext)
{

	D3D11_BLEND_DESC d3d11BlendDesc;
	d3d11BlendDesc.AlphaToCoverageEnable = false;
	d3d11BlendDesc.IndependentBlendEnable = false;
	d3d11BlendDesc.RenderTarget[0].BlendEnable = blendDesc.bBlendEnable;
	d3d11BlendDesc.RenderTarget[0].SrcBlend = HrD3D11Mapping::GetBlend(blendDesc.srcBlend);
	d3d11BlendDesc.RenderTarget[0].DestBlend = HrD3D11Mapping::GetBlend(blendDesc.dstBlend);
	d3d11BlendDesc.RenderTarget[0].BlendOp = HrD3D11Mapping::GetBlendOperation(blendDesc.blendOperation);
	d3d11BlendDesc.RenderTarget[0].SrcBlendAlpha = HrD3D11Mapping::GetBlend(blendDesc.srcBlendAlpha);
	d3d11BlendDesc.RenderTarget[0].DestBlendAlpha = HrD3D11Mapping::GetBlend(blendDesc.dstBlendAlpha);
	d3d11BlendDesc.RenderTarget[0].BlendOpAlpha = HrD3D11Mapping::GetBlendOperation(blendDesc.blendOperationAlpha);
	d3d11BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	TIF(m_pD3D11Device->CreateBlendState(&d3d11BlendDesc, &m_pD3D11BlendState));
}

HrD3D11BlendState::~HrD3D11BlendState()
{
	m_pD3D11BlendState->Release();
}

void HrD3D11BlendState::Bind(HrRender* pRender)
{
	HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11ImmediateContext();

	float blendFactor[4] = { 0.f,0.f,0.f,0.f };
	//开启“透明”效果
	pD3D11ImmediateContext->OMSetBlendState(m_pD3D11BlendState, blendFactor, 0xffffffff);
}
