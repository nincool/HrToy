#include "HrD3D11RenderLayout.h"
#include "HrD3D11Device.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11Shader.h"
#include "HrD3D11HardwareBuffer.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrVertext.h"
#include "HrCore/Include/HrLog.h"
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
		size_t nVertextElementNum = m_pVertext->GetVertextElementNum();
		m_pD3DInputElementDesc = new D3D11_INPUT_ELEMENT_DESC[nVertextElementNum];
		
		for (size_t i = 0; i < nVertextElementNum; ++i)
		{
			const HrVertextElement& vertextElement = m_pVertext->GetVertextElement(i);
			m_pD3DInputElementDesc[i].SemanticName = HrD3D11Mapping::GetInputElementSemanticName(vertextElement.m_elementUsage);
			m_pD3DInputElementDesc[i].SemanticIndex = 0;
			m_pD3DInputElementDesc[i].Format = HrD3D11Mapping::GetInputElementFormat(vertextElement.m_elementType);
			m_pD3DInputElementDesc[i].InputSlot = 0;
			m_pD3DInputElementDesc[i].AlignedByteOffset = vertextElement.GetOffset();
			m_pD3DInputElementDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			m_pD3DInputElementDesc[i].InstanceDataStepRate = 0;
		}

		HRESULT hr = HrD3D11Device::GetInstance().GetDevice()->CreateInputLayout(
			m_pD3DInputElementDesc,
			nVertextElementNum,
			pShader->GetStream()->GetBufferPoint(),
			pShader->GetStream()->GetBufferSize(),
			&m_pInputLayout);
	}
	return m_pInputLayout;
}

ID3D11Buffer* HrD3D11RenderLayout::GetVertexBuffer()
{
	return static_cast<HrD3D11HardwareBuffer*>(m_pHardwareBuffer)->GetVertextBuffer();
}

bool HrD3D11RenderLayout::CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer)
{
	DWORD shaderFlags = 0;//D3DCOMPILE_ENABLE_STRICTNESS;

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DCompileFromFile(pFilePath, 0, 0, pEntry, pTarget,
		shaderFlags, 0, pBuffer, &errorBuffer);
	if (FAILED(result))
	{
		if (errorBuffer != 0)
		{
			//char* pMsg = (char*)(errorBuffer->GetBufferPointer());
			HRERROR((LPCWSTR)errorBuffer->GetBufferPointer());
			errorBuffer->Release();
		}
		HRERROR(_T("CompileD3DShader Error! File[%s]"), pFilePath);
		return false;
	}

	if (errorBuffer != 0)
		errorBuffer->Release();

	return true;
}
