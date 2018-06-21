#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderD3D11/Include/HrD3D11Mapping.h"
#include "HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderD3D11/Include/HrD3D11Texture.h"
#include "HrRenderD3D11/Include/HrD3D11SamplerState.h"
#include "HrUtilTools/Include/HrUtil.h"

#include <boost/cast.hpp>

using namespace Hr;

void CHrD3D11SRVShaderParamRelationShip::UpdateShaderResourceView()
{
	HrTexture* pTex = nullptr;
	m_pTextureParam->Value(pTex);
	if (pTex)
	{
		*m_pD3D11SRV = HrCheckPointerCast<HrD3D11Texture2D>(pTex)->GetD3D11ShaderResourceView().get();
	}
}


////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////

HrD3D11Shader::HrD3D11Shader()
{
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;

	m_pShaderBuffer = HrMakeSharedPtr<HrStreamData>();
}

HrD3D11Shader::~HrD3D11Shader()
{


}

void HrD3D11Shader::Accept(const HrRenderPtr& pRender)
{
	for (size_t i = 0; i < m_vecBindRenderConstantBuffer.size(); ++i)
	{
		m_vecBindRenderConstantBuffer[i]->UpdateConstantBuffer();
	}

	for (size_t i = 0; i < m_vecSRVParamRelationships.size(); ++i)
	{
		m_vecSRVParamRelationships[i].UpdateShaderResourceView();
	}

	pRender->BindShader(shared_from_this());
}

void HrD3D11Shader::Unaccept(const HrRenderPtr& pRender)
{

}

void HrD3D11Shader::StreamIn(const HrStreamDataPtr& pStreamBuf, const std::string& strFile, const std::string& strName, EnumShaderType shaderType)
{
	m_shaderType = shaderType;
	m_strFilePath = strFile;
	m_strName = strName;
	m_nHashName = HrHashValue(strName);
	m_pShaderBuffer->CopyFrom(*pStreamBuf.get());

	switch (m_shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		CreateVertexShader();
		break;
	case HrShader::ST_PIXEL_SHADER:
		CreatePixelShader();
		break;
	default:
		break;
	}
}

void HrD3D11Shader::CreateVertexShader()
{
	ID3D11VertexShader* pVertexShader = nullptr;
	HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateVertexShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &pVertexShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreateVertexShader!"));
		return;
	}
	m_pVertexShader = MakeComPtr(pVertexShader);
}

void HrD3D11Shader::CreatePixelShader()
{
	ID3D11PixelShader* pPixelShader = nullptr;
	HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreatePixelShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &pPixelShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreatePixelShader!"));
		return;
	}
	m_pPixelShader = MakeComPtr(pPixelShader);
}

void HrD3D11Shader::BindRenderParameterImpl()
{
	BOOST_ASSERT(m_vecD3D11ConstBuffer.empty());
	for (size_t i = 0; i < m_vecBindRenderConstantBuffer.size(); ++i)
	{
		HrD3D11GraphicsBufferPtr pGraphicsBuffer = HrCheckPointerCast<HrD3D11GraphicsBuffer>(m_vecBindRenderConstantBuffer[i]->GetGraphicsBuffer());
		m_vecD3D11ConstBuffer.push_back(pGraphicsBuffer->GetD3DGraphicsBuffer().get());
	}

	BOOST_ASSERT(m_vecD3D11SRV.empty());
	m_vecSRVParamRelationships.clear();
	m_vecD3D11SRV.assign(m_vecBindRenderResources.size(), nullptr);
	for (size_t i = 0; i < m_vecBindRenderResources.size(); ++i)
	{
		m_vecSRVParamRelationships.emplace_back(m_vecBindRenderResources[i].get(), &m_vecD3D11SRV[i]);
	}
}

const ID3D11VertexShaderPtr& HrD3D11Shader::RetriveD3D11VertexShader()
{
	return m_pVertexShader;
}

const ID3D11PixelShaderPtr& HrD3D11Shader::RetriveD3D11PixelShader()
{
	return m_pPixelShader;
}

const std::vector<ID3D11Buffer*>& HrD3D11Shader::GetConstBuffers()
{
	return m_vecD3D11ConstBuffer;
}

const std::vector<ID3D11ShaderResourceView*>& Hr::HrD3D11Shader::GetSRVs()
{
	return m_vecD3D11SRV;
}

