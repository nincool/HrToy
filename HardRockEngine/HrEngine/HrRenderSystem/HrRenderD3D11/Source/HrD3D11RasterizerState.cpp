#include "HrD3D11RasterizerState.h"
#include "HrD3D11Mapping.h"

using namespace Hr;

HrD3D11RasterizerState::HrD3D11RasterizerState(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext, HrRasterizerState::RasterizerStateDesc& desc)
	:m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext), m_pRasterizerState(nullptr)
{
	CreateD3D11RasterizerState(desc);
}

HrD3D11RasterizerState::~HrD3D11RasterizerState()
{

}

void HrD3D11RasterizerState::Bind(HrRender* pRender)
{
	m_pImmediateContext->RSSetState(m_pRasterizerState);
}

ID3D11RasterizerState* HrD3D11RasterizerState::CreateD3D11RasterizerState(HrRasterizerState::RasterizerStateDesc& desc)
{
	if (m_pRasterizerState == nullptr)
	{
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = HrD3D11Mapping::GetFillMode(desc.fillMode);
		rasterizerDesc.CullMode = HrD3D11Mapping::GetCullMode(desc.cullMode);
		rasterizerDesc.FrontCounterClockwise = desc.bfrontCounterClockWise;
		rasterizerDesc.DepthClipEnable = desc.bDepthClipEnable;

		TIF(m_pD3D11Device->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState));
	}

	return m_pRasterizerState;
}
