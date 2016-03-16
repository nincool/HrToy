#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderWindow.h"
#include "HrD3D11RenderLayout.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrRenderDemo/Include/HrRenderDemo.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

#include "DirectXFX11/inc/d3dx11effect.h"
#include "HrMath/Include/HrMath.h"
#include "HrCore/Include/Asset/HrColor.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
	m_pD3D11ImmediateContext = nullptr;

	typedef HrRenderD3D11DemoPipleline DEMOCLASS;

	m_pRenderDemo = nullptr;
	//m_pRenderDemo = HR_NEW DEMOCLASS();

}

HrD3D11Render::~HrD3D11Render()
{
}

bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Device::GetInstance().CreateD3D11Device();
	
	m_pD3D11Device = HrD3D11Device::GetInstance().GetDevice();
	m_pD3D11ImmediateContext = HrD3D11Device::GetInstance().GetImmediateContext();

	m_pShareRenderWindow = MakeSharedPtr<HrD3D11RenderWindow>();
	m_pShareRenderWindow->CreateRenderWindow(nWidth, nHeight, lpfnProc);

	if (m_pRenderDemo)
	{
		m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance().GetDevice()
			, HrD3D11Device::GetInstance().GetImmediateContext()
			, m_pShareRenderWindow->GetRenderTargetView()
			, m_pShareRenderWindow->GetDepthStencilView()
			, m_pShareRenderWindow->GetSwapChain());
		if (!m_pRenderDemo->Init())
		{
			return false;
		}
	}

	LoadContent();
	return true;
}

void HrD3D11Render::Release()
{
	HrD3D11Device::GetInstance().Release();
	if (m_pRenderDemo)
		m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	return true;
}

void HrD3D11Render::Render(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout)
{
	if (m_pRenderDemo)
	{
		m_pRenderDemo->Render();
		return;
	}
	TestRender(pRenderTechnique, pRenderLayout);
	return;
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pShareRenderWindow->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pShareRenderWindow->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	unsigned int offset = 0;

	IShader* pShader = pRenderTechnique->GetRenderPass(0)->GetVertexShader();
	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout(static_cast<HrD3D11Shader*>(pShader));
	m_pD3D11ImmediateContext->IASetInputLayout(pInputLayout);
	
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (pD3D11RenderLayout->UseIndices())
	{
		ID3D11Buffer* pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
		m_pD3D11ImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	}

	if (pD3D11RenderLayout->UseIndices())
	{
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}
	else
	{
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->Draw(3, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}

	m_pShareRenderWindow->GetSwapChain()->Present(0, 0);
}

bool HrD3D11Render::LoadContent()
{
	m_pShareCamera = std::make_shared<HrCamera>();

	ID3DBlob* pShaderBuffer(nullptr);
	bool bCompile = CompileD3DShader(L"Media\\HrShader\\BasicDraw.hlsl", "VS_Main", "vs_5_0", &pShaderBuffer);
	//从编译好的effect中创建effect
	ID3DBlob* pEffectShaderBuffer = nullptr;
	bCompile = CompileD3DShader(L"Media\\HrShader\\BasicDraw.fx", nullptr, "fx_5_0", &pEffectShaderBuffer);
	HRESULT rt;
	rt = D3DX11CreateEffectFromMemory(pEffectShaderBuffer->GetBufferPointer(), pEffectShaderBuffer->GetBufferSize(), 0, m_pD3D11Device, &m_pEffect);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateEffectFromMemory Error!"));
		return false;
	}
	
	m_pSolidColorVS = nullptr;
	rt = m_pD3D11Device->CreateVertexShader(pShaderBuffer->GetBufferPointer(),
		pShaderBuffer->GetBufferSize(), 0, &m_pSolidColorVS);
	if (FAILED(rt))
	{
		if (pShaderBuffer)
			pShaderBuffer->Release();

		return false;
	}
	

	//开始创建输入布局
	D3D11_INPUT_ELEMENT_DESC inputDesc[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	D3DX11_PASS_DESC passDesc = { 0 };
	m_pEffect->GetTechniqueByName("BasicDraw")->GetPassByIndex(0)->GetDesc(&passDesc);
	//rt = m_pD3D11Device->CreateInputLayout(inputDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pInputLayout);

	rt = m_pD3D11Device->CreateInputLayout(inputDesc, 2,
		pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize(), &m_pInputLayout);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateInputLayout Error"));
		return false;
	}
	SAFE_RELEASE(pShaderBuffer);

	ID3DBlob* psBuffer = 0;
	bCompile = CompileD3DShader(L"Media\\HrShader\\BasicDraw.hlsl", "PS_Main", "ps_4_0", &psBuffer);
	if (!bCompile)
	{
		return false;
	}

	rt = m_pD3D11Device->CreatePixelShader(psBuffer->GetBufferPointer(),
		psBuffer->GetBufferSize(), 0, &m_pSolidColorPS);

	psBuffer->Release();

	struct Vertex
	{
		float3 position;
		float4 color;
	};

	Vertex vertices[8] =
	{
		{ float3(-1.0f, -1.0f, -1.0f), HrColor::F4Blue },
		{ float3(-1.0f, 1.0f, -1.0f), HrColor::F4Cyan },
		{ float3(1.0f, 1.0f, -1.0f), HrColor::F4Red },
		{ float3(1.0f, -1.0f, -1.0f), HrColor::F4Yellow },
		{ float3(-1.0f, -1.0f, 1.0f), HrColor::F4Green },
		{ float3(-1.0f, 1.0f, 1.0f), HrColor::F4Silver },
		{ float3(1.0f, 1.0f, 1.0f), HrColor::F4Black },
		{ float3(1.0f, -1.0f, 1.0f), HrColor::F4Magenta }
	};

	//创建顶点缓存
	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = 8 * sizeof(Vertex);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vbData = { 0 };
	vbData.pSysMem = vertices;
	rt = m_pD3D11Device->CreateBuffer(&vbDesc, &vbData, &m_pVertexBuffer);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateVertexBuffer Error!"));
		return false;
	}

	//创建索引缓存
	D3D11_BUFFER_DESC ibDesc = { 0 };
	ibDesc.ByteWidth = 36 * sizeof(UINT);
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
	UINT indices[36] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 1, 4, 1, 0,
		7, 6, 5, 7, 5, 4,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};
	D3D11_SUBRESOURCE_DATA ibData = { 0 };
	ibData.pSysMem = indices;
	rt = m_pD3D11Device->CreateBuffer(&ibDesc, &ibData, &m_pIndexBuffer);
	if (FAILED(rt))
	{

		HRERROR(_T("CreateIndexBuffer Error!"));
		return false;
	}

	//连接Shader变量与C++
	m_pFxWorldViewProj = m_pEffect->GetVariableByName("g_worldViewProj")->AsMatrix();

	return true;
}

bool HrD3D11Render::TestRender(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout)
{
	//
	static float phy(0.0f), theta(0.0f);
	XMMATRIX rotation1 = XMMatrixRotationY(phy);
	XMMATRIX rotation2 = XMMatrixRotationX(theta);
	phy += XM_PI * 0.5f * 0.001f;
	theta += XM_PI * 0.5f * 0.001f;

	//视变换 把摄像机变换到世界坐标系原点 所有物体都随摄像机变换 
	XMMATRIX world = XMMatrixIdentity();
	//world = rotation1 * rotation2;

	//视变换 把摄像机变换到世界坐标系原点 所有物体都随摄像机变换 
	XMVECTOR eyePos = XMVectorSet(0.0f, 2.0f, -5.0f, 1.0f);
	XMVECTOR lookAt = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX view = XMMatrixLookAtLH(eyePos, lookAt, up);

	//投影变换
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	XMMATRIX worldViewProj = world * view * proj;

	//投影变换
	m_pShareCamera->ViewParams(Vector3(0.0f, 2.0, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_pShareCamera->ProjectParams(Hr::PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	Matrix4 projMatrix = m_pShareCamera->GetProjectMatrix();
	Matrix4 viewMatrix = m_pShareCamera->GetViewMatrix();

	Matrix4 worldViewProjMatrix = viewMatrix * projMatrix;

	//更新Shader相应的变量
	m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProjMatrix));

	XMVECTORF32 Blue = { 0.0f, 0.0f, 0.25f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pShareRenderWindow->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pShareRenderWindow->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//{
	//	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	//	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	//	unsigned int offset = 0;

	//	IShader* pShader = pRenderTechnique->GetRenderPass(0)->GetVertexShader();
	//	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout(static_cast<HrD3D11Shader*>(pShader));
	//	m_pD3D11ImmediateContext->IASetInputLayout(pInputLayout);

	//	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	//	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	//	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//	if (pD3D11RenderLayout->UseIndices())
	//	{
	//		ID3D11Buffer* pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
	//		m_pD3D11ImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//	}
	//}

	
	{
		//指定输入布局
		m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);
		struct Vertex
		{
			float3 position;
			float4 color;
		};
		uint32 nStride = sizeof(Vertex);
		uint32 nOffset = 0;
		m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
		//指定索引缓存
		m_pD3D11ImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//指定图元拓扑类型
		m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}



	//{
	//	//if (pD3D11RenderLayout->UseIndices())
	//	if (true)
	//	{
	//		pRenderTechnique->GetRenderPass(0)->BindPass(this);
	//		m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);
	//		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	//	}
	//	else
	//	{
	//		pRenderTechnique->GetRenderPass(0)->BindPass(this);
	//		m_pD3D11ImmediateContext->Draw(3, 0);
	//		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	//	}
	//}

	{
		//{
		//	//从Technique获取全部pass并逐个渲染
		//	ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByName("BasicDraw");
		//	D3DX11_TECHNIQUE_DESC techDesc = { 0 };
		//	pTech->GetDesc(&techDesc);
		//	for (UINT i = 0; i < techDesc.Passes; ++i)
		//	{
		//		pTech->GetPassByIndex(i)->Apply(0, m_pD3D11ImmediateContext);
		//		m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);
		//	}
		//}

		ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByName("BasicDraw"); 
		ID3DX11EffectPass* pPass  = pTech->GetPassByIndex(0);
		D3DX11_PASS_SHADER_DESC passVertexShaderDesc;
		pPass->GetVertexShaderDesc(&passVertexShaderDesc);
		ID3D11VertexShader* pVertexShader = nullptr;
		passVertexShaderDesc.pShaderVariable->GetVertexShader(0, &pVertexShader);
		D3DX11_PASS_SHADER_DESC passPixShaderDesc;
		pPass->GetPixelShaderDesc(&passPixShaderDesc);
		ID3D11PixelShader* pPixShader = nullptr;
		passPixShaderDesc.pShaderVariable->GetPixelShader(0, &pPixShader);


		{
			ID3D11Buffer* m_pD3D11ConstBuffer = nullptr;

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(float) * 16;
			uint32 nSize = sizeof(worldViewProjMatrix);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			HRESULT rt = m_pD3D11Device->CreateBuffer(&bd, NULL, &m_pD3D11ConstBuffer);

			D3D11_MAPPED_SUBRESOURCE mappedResource;

			struct PerFrame
			{
				Matrix4 matrix;
			};
			XMMATRIX transposeMatrix = XMMatrixTranspose(worldViewProj);
			Matrix4 transposMatrix2 = HrMath::Transpose(worldViewProjMatrix);
			rt = m_pD3D11ImmediateContext->Map(m_pD3D11ConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy((char*)mappedResource.pData, (char*)reinterpret_cast<float*>(&transposMatrix2), sizeof(float) * 16);
			//((PerFrame*)mappedResource.pData)->matrix = HrMath::Transpose(worldViewProjMatrix);
			//((PerFrame*)mappedResource.pData)->matrix = worldViewProjMatrix;
			m_pD3D11ImmediateContext->Unmap(m_pD3D11ConstBuffer, 0);

			m_pD3D11ImmediateContext->VSSetConstantBuffers(0, 1, &m_pD3D11ConstBuffer);
			
			m_pD3D11ImmediateContext->VSSetShader(m_pSolidColorVS, 0, 0);
			m_pD3D11ImmediateContext->PSSetShader(m_pSolidColorPS, 0, 0);

			m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);

			SAFE_RELEASE(m_pD3D11ConstBuffer);
		}
	}

	m_pShareRenderWindow->GetSwapChain()->Present(0, 0);

	return true;
}