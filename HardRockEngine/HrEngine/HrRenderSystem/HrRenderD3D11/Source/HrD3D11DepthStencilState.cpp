#include "HrD3D11DepthStencilState.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11Render.h"

using namespace Hr;

HrD3D11DepthStencilState::HrD3D11DepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilDesc)
{
	D3D11_DEPTH_STENCIL_DESC d3d11DepthStencilDesc;
	d3d11DepthStencilDesc.DepthEnable = depthStencilDesc.bDepthEnable;
	d3d11DepthStencilDesc.DepthWriteMask = HrD3D11Mapping::GetDepthWriteMask(depthStencilDesc.depthWriteMask);
	d3d11DepthStencilDesc.DepthFunc = HrD3D11Mapping::GetComparisonFunc(depthStencilDesc.depthCompareFunc);
	d3d11DepthStencilDesc.StencilEnable = depthStencilDesc.bStencilEnable;
	d3d11DepthStencilDesc.StencilReadMask = depthStencilDesc.stencilReadMask;
	d3d11DepthStencilDesc.StencilWriteMask = depthStencilDesc.stencilWriteMask;
	d3d11DepthStencilDesc.FrontFace.StencilFunc = HrD3D11Mapping::GetComparisonFunc(depthStencilDesc.frontFaceCompareFunc);
	d3d11DepthStencilDesc.FrontFace.StencilFailOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.frontFaceStencilFailOp);
	d3d11DepthStencilDesc.FrontFace.StencilDepthFailOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.frontFaceStencilDepthFailOp);
	d3d11DepthStencilDesc.FrontFace.StencilPassOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.frontFaceStencilPassOp);
	d3d11DepthStencilDesc.BackFace.StencilFunc = HrD3D11Mapping::GetComparisonFunc(depthStencilDesc.backFaceCompareFunc);
	d3d11DepthStencilDesc.BackFace.StencilFailOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.backFaceStencilFailOp);
	d3d11DepthStencilDesc.BackFace.StencilDepthFailOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.backFaceStencilDepthFailOp);
	d3d11DepthStencilDesc.BackFace.StencilPassOp = HrD3D11Mapping::GetDepthStencilOperation(depthStencilDesc.backFaceStencilPassOp);
	m_nStencilRef = depthStencilDesc.nStencilRef;

	ID3D11DepthStencilState* pD3D11DepthStencilState = nullptr;
	TIF(HrD3D11Device::Instance()->GetD3DDevice()->CreateDepthStencilState(&d3d11DepthStencilDesc, &pD3D11DepthStencilState));
	m_pD3D11DepthStencilState = MakeComPtr(pD3D11DepthStencilState);
}

HrD3D11DepthStencilState::~HrD3D11DepthStencilState()
{
}

const ID3D11DepthStencilStatePtr& HrD3D11DepthStencilState::RetriveD3D11DepthStencil()
{
	return m_pD3D11DepthStencilState;
}

uint32 HrD3D11DepthStencilState::GetStencilRef()
{
	return m_nStencilRef;
}

void HrD3D11DepthStencilState::Accept(const HrRenderPtr& pRender)
{
	pRender->BindDepthStencilState(shared_from_this());
}


