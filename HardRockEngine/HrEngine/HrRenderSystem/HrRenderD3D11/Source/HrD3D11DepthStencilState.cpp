#include "HrD3D11DepthStencilState.h"
#include "HrD3D11Mapping.h"

using namespace Hr;

HrD3D11DepthStencilState::HrD3D11DepthStencilState(ID3D11Device* pD3D11Device
	, ID3D11DeviceContext* pContext
	, const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilDesc)
	:m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext)
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

	TIF(m_pD3D11Device->CreateDepthStencilState(&d3d11DepthStencilDesc, &m_pD3D11DepthStencilState));
}

HrD3D11DepthStencilState::~HrD3D11DepthStencilState()
{
	m_pD3D11DepthStencilState->Release();
}

void HrD3D11DepthStencilState::Bind(HrRender* pRender)
{
	m_pImmediateContext->OMSetDepthStencilState(m_pD3D11DepthStencilState, 0xffffffff);
}

