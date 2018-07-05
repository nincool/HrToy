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
{}

HrD3D11RenderLayout::~HrD3D11RenderLayout()
{
}

void HrD3D11RenderLayout::Active()
{
	if (m_bStreamsDirty)
	{
		const uint32 nVertexStreams = GetVertexStreamSize();

		m_vecD3DVertexBuffer.clear();
		m_vecInputElementDesc.clear();
		m_vecStrides.clear();
		m_vecOffsets.clear();

		for (uint32 i = 0; i < nVertexStreams; ++i)
		{
			const HrVertexDataPtr& pVertexData = m_vecVertexStreams[i];
			for (uint32 nEleIndex = 0; nEleIndex < pVertexData->GetVertex()->GetVertexElementNum(); ++nEleIndex)
			{
				const HrVertexElement& vertexElement = pVertexData->GetVertex()->GetVertexElement(nEleIndex);
				D3D11_INPUT_ELEMENT_DESC d3dInputELeDesc;
				d3dInputELeDesc.SemanticName = HrD3D11Mapping::GetInputElementSemanticName(vertexElement.m_elementSemantic);
				d3dInputELeDesc.SemanticIndex = vertexElement.m_nSemanticIndex;
				d3dInputELeDesc.Format = HrD3D11Mapping::GetInputElementFormat(vertexElement.m_elementType);
				d3dInputELeDesc.InputSlot = i;
				d3dInputELeDesc.AlignedByteOffset = vertexElement.GetOffset();
				d3dInputELeDesc.InputSlotClass = HrD3D11Mapping::GetInputELementClassType(vertexElement.m_elementClassType);
				d3dInputELeDesc.InstanceDataStepRate = vertexElement.m_nInstanceStepRate;
				m_vecInputElementDesc.emplace_back(d3dInputELeDesc);
			}
			const HrD3D11GraphicsBufferPtr & pVertexStream = HrCheckPointerCast<HrD3D11GraphicsBuffer>(pVertexData->GetVertexStream());
			m_vecD3DVertexBuffer.push_back(pVertexStream->GetD3DGraphicsBuffer().get());
			m_vecStrides.push_back(pVertexData->GetVertex()->GetVertexSize());
			m_vecOffsets.push_back(0);
		}
		
		m_bStreamsDirty = false;
	}
}

const ID3D11InputLayoutPtr& HrD3D11RenderLayout::GetInputLayout(const HrD3D11ShaderPtr& pShader)
{
	for (const auto& iteLayout : m_vecInputLayouts)
	{
		if (iteLayout.first == pShader->HashName())
		{
			return iteLayout.second;
		}
	}

	ID3D11InputLayout* pD3DInputLayout = nullptr;
	HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateInputLayout(
		&m_vecInputElementDesc[0],
		m_vecInputElementDesc.size(),
		pShader->GetCodeData()->GetBufferPoint(),
		pShader->GetCodeData()->GetBufferSize(),
		&pD3DInputLayout);
	if (FAILED(hr))
	{
		TRE("HrD3D11RenderLayout::GetInput Error!");
	}
	else
	{
		ID3D11InputLayoutPtr pD3DIL = MakeComPtr(pD3DInputLayout);
		m_vecInputLayouts.emplace_back(pShader->HashName(), pD3DIL);

		return m_vecInputLayouts.back().second;
	}

	return nullptr;
}

const std::vector<ID3D11Buffer*>& HrD3D11RenderLayout::GetD3DVertexBuffers()
{
	return m_vecD3DVertexBuffer;
}

const std::vector<UINT>& HrD3D11RenderLayout::GetStrides()
{
	return m_vecStrides;
}

const std::vector<UINT>& HrD3D11RenderLayout::GetOffsets()
{
	return m_vecOffsets;
}

