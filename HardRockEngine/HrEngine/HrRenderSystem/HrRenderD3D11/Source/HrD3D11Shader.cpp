#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include <boost/cast.hpp>
#include <d3dcompiler.h>
#include "HrCore/Include/HrLog.h"

using namespace Hr;

HrD3D11Shader::HrD3D11Shader()
{
	m_pShaderBuffer = HR_NEW HrStreamData();
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
}

HrD3D11Shader::~HrD3D11Shader()
{
	SAFE_DELETE(m_pShaderBuffer);
}

void HrD3D11Shader::Bind(IRender* pRender)
{
	HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11ImmediateContext();

	pD3D11ImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);
	pD3D11ImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
}

void HrD3D11Shader::UnBind(IRender* pRender)
{

}

void HrD3D11Shader::StreamIn(HrStreamData& streamData)
{
	if (!CompileShader(streamData))
	{
		return;
	}

	switch (m_shaderType)
	{
	case IShader::ST_VERTEX_SHADER:
		CreateVertexShader();
		break;
	case IShader::ST_PIXEL_SHADER:
		CreatePixelShader();
		break;
	default:
		break;
	}
}

bool HrD3D11Shader::CompileShader(HrStreamData& streamData)
{
	char* pSource = streamData.GetBufferPoint();
	uint64 nSize = streamData.GetBufferSize();

	ID3DBlob* pShaderBuffer = nullptr;
	ID3DBlob* pErrorBuffer = nullptr;

	std::string strShaderModel = "";
	switch (m_shaderType)
	{
	case Hr::IShader::ST_VERTEX_SHADER:
		strShaderModel = "vs_5_0";
		break;
	case Hr::IShader::ST_PIXEL_SHADER:
		strShaderModel = "ps_5_0";
		break;
	default:
		break;
	}

	HRESULT hr = D3DCompile(
		pSource,              // [in] Pointer to the shader in memory. 
		nSize,                // [in] Size of the shader in memory.  
		nullptr,              // [in] Optional. You can use this parameter for strings that specify error messages.
		nullptr,              // [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL. 
		nullptr,              // [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
		m_strEntryPoint.c_str(),  // [in] Name of the shader-entrypoint function where shader execution begins. 
		strShaderModel.c_str(),   // [in] A string that specifies the shader model; can be any profile in shader model 4 or higher. 
		0,                    // [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
		NULL,                 // [in] Effect compile flags
		&pShaderBuffer,       // [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
		&pErrorBuffer         // [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
		);
	if (FAILED(hr))
	{
		if (pErrorBuffer != 0)
		{
			char* pMsg = (char*)(pErrorBuffer->GetBufferPointer());
			pErrorBuffer->Release();
		}
		HRERROR(_T("CompileD3DShader Error! File"));
		return false;
	}

	if (pErrorBuffer != 0)
		pErrorBuffer->Release();

	m_pShaderBuffer->ResizeBuffer(pShaderBuffer->GetBufferSize());
	memcpy(m_pShaderBuffer->GetBufferPoint(), pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize());

	pShaderBuffer->Release();

	return true;
}

void HrD3D11Shader::CreateVertexShader()
{
	HRESULT hr = HrD3D11Device::GetInstance().GetDevice()->CreateVertexShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &m_pVertexShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreateVertexShader!"));
		return;
	}
}

void HrD3D11Shader::CreatePixelShader()
{
	HRESULT hr = HrD3D11Device::GetInstance().GetDevice()->CreatePixelShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &m_pPixelShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreatePixelShader!"));
		return;
	}
}







