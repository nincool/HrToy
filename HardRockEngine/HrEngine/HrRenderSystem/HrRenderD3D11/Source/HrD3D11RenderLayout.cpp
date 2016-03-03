#include "HrD3D11RenderLayout.h"
#include "HrD3D11Device.h"
#include "HrCore/Include/HrLog.h"
#include <D3Dcompiler.h>

using namespace Hr;

HrD3D11RenderLayout::HrD3D11RenderLayout()
{
	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;

	m_pSolidColorPS = nullptr;
	m_pSolidColorVS = nullptr;
}

ID3D11InputLayout* HrD3D11RenderLayout::GetInputLayout()
{
	if (m_pInputLayout == nullptr)
	{
		ID3DBlob* vsBuffer = 0;

		bool compileResult = CompileD3DShader(L"HrShader\\SolidGreenColor.fx", "VS_Main", "vs_4_0", &vsBuffer);
		if (compileResult == false)
		{
			return false;
		}

		HRESULT d3dResult;

		d3dResult = HrD3D11Device::GetInstance().GetDevice()->CreateVertexShader(vsBuffer->GetBufferPointer(),
			vsBuffer->GetBufferSize(), 0, &m_pSolidColorVS);
		if (FAILED(d3dResult))
		{
			if (vsBuffer)
				vsBuffer->Release();

			return false;
		}

		D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);
		d3dResult = HrD3D11Device::GetInstance().GetDevice()->CreateInputLayout(solidColorLayout, totalLayoutElements,
			vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &m_pInputLayout);
		vsBuffer->Release();

		if (FAILED(d3dResult))
		{
			return false;
		}

		ID3DBlob* psBuffer = 0;
		compileResult = CompileD3DShader(L"HrShader\\SolidGreenColor.fx", "PS_Main", "ps_4_0", &psBuffer);
		if (compileResult == false)
		{
			return false;
		}

		d3dResult = HrD3D11Device::GetInstance().GetDevice()->CreatePixelShader(psBuffer->GetBufferPointer(),
			psBuffer->GetBufferSize(), 0, &m_pSolidColorPS);

		psBuffer->Release();

		if (FAILED(d3dResult))
		{
			return false;
		}
	}
	return m_pInputLayout;
}

ID3D11Buffer* HrD3D11RenderLayout::GetVertexBuffer()
{
	if (m_pVertexBuffer == nullptr)
	{
		VertexPos vertices[] =
		{
			XMFLOAT3(0.5f, 0.5f, 0.5f),
			XMFLOAT3(0.5f, -0.5f, 0.5f),
			XMFLOAT3(-0.5f, -0.5f, 0.5f)
		};

		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = sizeof(VertexPos) * 3;

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = vertices;

		bool d3dResult = HrD3D11Device::GetInstance().GetDevice()->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);

		if (FAILED(d3dResult))
		{
			return false;
		}
	}

	return m_pVertexBuffer;
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

uint32 HrD3D11RenderLayout::GetVertextSize()
{
	return sizeof(VertexPos);
}
