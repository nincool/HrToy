#include "HrD3D11RenderLayout.h"
#include "HrD3D11Device.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11Shader.h"
#include "HrD3D11GraphicsBuffer.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include <D3Dcompiler.h>

using namespace Hr;

HrD3D11RenderLayout::HrD3D11RenderLayout()
{
	m_pD3DInputLayout = nullptr;
	m_pD3DVertexBuffer = nullptr;

	m_pD3DInputElementDesc = nullptr;
}

Hr::HrD3D11RenderLayout::~HrD3D11RenderLayout()
{
	SAFE_DELETE_ARRAY(m_pD3DInputElementDesc);
}

const ID3D11InputLayoutPtr& HrD3D11RenderLayout::GetInputLayout(const HrD3D11ShaderPtr& pShader)
{
	if (m_pD3DInputLayout == nullptr)
	{
		size_t nVertexElementNum = m_pVertex->GetVertexElementNum();
		m_pD3DInputElementDesc = new D3D11_INPUT_ELEMENT_DESC[nVertexElementNum];
		memset(m_pD3DInputElementDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
		for (size_t i = 0; i < nVertexElementNum; ++i)
		{
			const HrVertexElement& VertexElement = m_pVertex->GetVertexElement(i);
			m_pD3DInputElementDesc[i].SemanticName = HrD3D11Mapping::GetInputElementSemanticName(VertexElement.m_elementUsage);
			m_pD3DInputElementDesc[i].SemanticIndex = 0;
			m_pD3DInputElementDesc[i].Format = HrD3D11Mapping::GetInputElementFormat(VertexElement.m_elementType);
			m_pD3DInputElementDesc[i].InputSlot = 0;
			m_pD3DInputElementDesc[i].AlignedByteOffset = VertexElement.GetOffset();
			m_pD3DInputElementDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			m_pD3DInputElementDesc[i].InstanceDataStepRate = 0;
		}

		ID3D11InputLayout* pD3DInputLayout = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateInputLayout(
			m_pD3DInputElementDesc,
			nVertexElementNum,
			pShader->GetCodeData()->GetBufferPoint(),
			pShader->GetCodeData()->GetBufferSize(),
			&pD3DInputLayout);
		if (FAILED(hr))
		{
			TRE("HrD3D11RenderLayout::GetInput Error!");
		}
		else
		{
			m_pD3DInputLayout = MakeComPtr(pD3DInputLayout);
		}
	}
	return m_pD3DInputLayout;
}

const ID3D11BufferPtr& HrD3D11RenderLayout::GetVertexBuffer()
{
	return (HrCheckPointerCast<HrD3D11GraphicsBuffer>(m_pVertexBuffer))->GetD3DGraphicsBuffer();
}

const ID3D11BufferPtr& HrD3D11RenderLayout::GetIndexBuffer()
{
	return (HrCheckPointerCast<HrD3D11GraphicsBuffer>(m_pIndexBuffer))->GetD3DGraphicsBuffer();
}


