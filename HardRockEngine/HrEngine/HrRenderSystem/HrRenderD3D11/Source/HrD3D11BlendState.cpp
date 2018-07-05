#include "HrD3D11BlendState.h"
#include "HrD3D11Render.h"
#include "HrD3D11Mapping.h"

#include <boost/cast.hpp>

using namespace Hr;

HrD3D11BlendState::HrD3D11BlendState(const HrBlendState::HrBlendStateDesc& blendDesc)
{
	m_nHashName = blendDesc.hashName;

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
	d3d11BlendDesc.RenderTarget[0].RenderTargetWriteMask = HrD3D11Mapping::GetRenderTargetWriteMask(blendDesc.colorMask);
	ID3D11BlendState* pD3D11BlendState = nullptr;
	TIF(HrD3D11Device::Instance()->GetD3DDevice()->CreateBlendState(&d3d11BlendDesc, &pD3D11BlendState));
	m_pD3D11BlendState = MakeComPtr(pD3D11BlendState);

	m_blendFactorColor = blendDesc.blendFactor;
	m_nSampleMask = blendDesc.nSampleMask;
}

HrD3D11BlendState::~HrD3D11BlendState()
{
}

void HrD3D11BlendState::Accept(const HrRenderPtr& pRender)
{
	pRender->BindBlendState(shared_from_this());
}

const ID3D11BlendStatePtr& HrD3D11BlendState::RetriveD3D11BlendState()
{
	return m_pD3D11BlendState;
}

const HrColor& HrD3D11BlendState::GetBlendFactor()
{
	return m_blendFactorColor;
}

uint32 HrD3D11BlendState::GetSampleMask()
{
	return m_nSampleMask;
}
