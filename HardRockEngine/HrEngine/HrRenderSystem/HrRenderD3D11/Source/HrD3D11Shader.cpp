#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include <boost/cast.hpp>
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"

using namespace Hr;

HrD3D11Shader::HrD3D11Shader()
{
	m_pVSShader = nullptr;
	m_pPSShader = nullptr;
}

HrD3D11Shader::~HrD3D11Shader()
{

}

void HrD3D11Shader::Bind(IRender* pRender)
{
	HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11ImmediateContext();

	pD3D11ImmediateContext->VSSetShader(m_pVSShader, nullptr, 0);
	pD3D11ImmediateContext->PSSetShader(m_pPSShader, nullptr, 0);
}

void HrD3D11Shader::UnBind(IRender* pRender)
{

}



