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
	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;

	m_pSolidColorPS = nullptr;
	m_pSolidColorVS = nullptr;

	m_pD3DInputElementDesc = nullptr;
}

Hr::HrD3D11RenderLayout::~HrD3D11RenderLayout()
{
	SAFE_DELETE_ARRAY(m_pD3DInputElementDesc);
}

ID3D11InputLayout* HrD3D11RenderLayout::GetInputLayout(HrD3D11Shader* pShader)
{
	if (m_pInputLayout == nullptr)
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

		HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreateInputLayout(
			m_pD3DInputElementDesc,
			nVertexElementNum,
			pShader->GetStream()->GetBufferPoint(),
			pShader->GetStream()->GetBufferSize(),
			&m_pInputLayout);
		if (FAILED(hr))
		{
			if (m_pInputLayout)
				m_pInputLayout->Release();
		}
	}
	return m_pInputLayout;
}

ID3D11Buffer* HrD3D11RenderLayout::GetVertexBuffer()
{
	return static_cast<HrD3D11GraphicsBuffer*>(m_pHDVertexBuffer)->GetGraphicsBuffer();
}

ID3D11Buffer* HrD3D11RenderLayout::GetIndexBuffer()
{
	return static_cast<HrD3D11GraphicsBuffer*>(m_pHDIndexBuffer)->GetGraphicsBuffer();
}


