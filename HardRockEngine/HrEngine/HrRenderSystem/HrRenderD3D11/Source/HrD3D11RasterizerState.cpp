#include "HrD3D11RasterizerState.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11Render.h"

using namespace Hr;

HrD3D11RasterizerState::HrD3D11RasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc) : m_pRasterizerState(nullptr)
{
	CreateD3D11RasterizerState(desc);
}


HrD3D11RasterizerState::~HrD3D11RasterizerState()
{

}

void HrD3D11RasterizerState::Accept(const HrRenderPtr& pRender)
{
	pRender->BindRasterizerState(shared_from_this());
}

void HrD3D11RasterizerState::CreateD3D11RasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc)
{
	if (m_pRasterizerState == nullptr)
	{
		//typedef struct D3D11_RASTERIZER_DESC {
		//	D3D11_FILL_MODE FillMode; // Default: D3D11_FILL_SOLID
		//	D3D11_CULL_MODE CullMode; // Default: D3D11_CULL_BACK
		//	BOOL FrontCounterClockwise; // Default: false
		//	INT DepthBias; // Default: 0
		//	FLOAT DepthBiasClamp; // Default: 0.0f
		//	FLOAT SlopeScaledDepthBias; // Default: 0.0f
		//	BOOL DepthClipEnable; // Default: true
		//	BOOL ScissorEnable; // Default: false
		//	BOOL MultisampleEnable; // Default: false
		//	BOOL AntialiasedLineEnable; // Default: false
		//} D3D11_RASTERIZER_DESC;

		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = HrD3D11Mapping::GetFillMode(desc.fillMode);
		rasterizerDesc.CullMode = HrD3D11Mapping::GetCullMode(desc.cullMode);
		rasterizerDesc.FrontCounterClockwise = desc.bfrontCounterClockWise;
		rasterizerDesc.DepthBias = desc.nDepthBias;
		rasterizerDesc.DepthBiasClamp = desc.fDepthBiasClamp;
		rasterizerDesc.SlopeScaledDepthBias = desc.fSlopScaleDepthBias;
		rasterizerDesc.DepthClipEnable = desc.bDepthClipEnable;
		rasterizerDesc.ScissorEnable = desc.bScissorEnable;
		rasterizerDesc.MultisampleEnable = desc.bMultisampleEnalbe;
		rasterizerDesc.AntialiasedLineEnable = desc.bAntialiaseLineEnable;

		ID3D11RasterizerState* pRasterizerState = nullptr;
		TIF(HrD3D11Device::Instance()->GetD3DDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterizerState));
		m_pRasterizerState = MakeComPtr(pRasterizerState);
	}
}

const ID3D11RasterizerStatePtr& HrD3D11RasterizerState::RetriveD3D11RasterizerState()
{
	return m_pRasterizerState;
}
