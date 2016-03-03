#include "HrRenderD3D11DemoGeometry.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/WICTextureLoader.h"
#include "DirectXTK/Inc/SpriteBatch.h"
#include "DirectXFX11/inc/d3dx11effect.h"
#include <fstream>

using namespace Hr;
using namespace std;
using namespace DirectX;

const XMFLOAT4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
const XMFLOAT4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const XMFLOAT4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
const XMFLOAT4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
const XMFLOAT4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
const XMFLOAT4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
const XMFLOAT4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
const XMFLOAT4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
const XMFLOAT4 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };

HrRenderD3D11DemoGeometry::HrRenderD3D11DemoGeometry()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_pSwapChain = nullptr;

	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;

	m_pEffect = nullptr;
	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;

	m_pFxWorldViewProj = nullptr;
}

void HrRenderD3D11DemoGeometry::SetD3DDevice(ID3D11Device* pDevice
	, ID3D11DeviceContext* pDeviceContex
	, ID3D11RenderTargetView* pRenderTargetView
	, ID3D11DepthStencilView* pDepthStencilView
	, IDXGISwapChain* pSwapChain)
{
	m_pD3D11Device = pDevice;
	m_pD3D11ImmediateContext = pDeviceContex;
	m_pRenderTargetView = pRenderTargetView;
	m_pDepthStencilView = pDepthStencilView;
	m_pSwapChain = pSwapChain;

}

bool HrRenderD3D11DemoGeometry::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoGeometry::LoadContent()
{
	BuildHLSL();
	BuildInputLayout();
	BuildBuffers();

	return true;
}

bool HrRenderD3D11DemoGeometry::Render()
{
	static float phy(0.0f), theta(0.0f);
	XMMATRIX rotation1 = XMMatrixRotationY(phy);
	XMMATRIX rotation2 = XMMatrixRotationX(theta);
	phy += XM_PI * 0.5f * 0.001f;
	theta += XM_PI * 0.5f * 0.001f;

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

	//更新Shader相应的变量
	m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//指定输入布局
	m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);

	uint32 nStride = sizeof(VertexPos);
	uint32 nOffset = 0;
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
	//指定索引缓存
	m_pD3D11ImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//指定图元拓扑类型
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//设置为“线框”绘制模式
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.DepthClipEnable = true;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;		//WireFrame
	rsDesc.FrontCounterClockwise = false;
	ID3D11RasterizerState *rsState(NULL);
	m_pD3D11Device->CreateRasterizerState(&rsDesc, &rsState);
	m_pD3D11ImmediateContext->RSSetState(rsState);

	//从Technique获取全部pass并逐个渲染
	ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByName("BasicDraw");
	D3DX11_TECHNIQUE_DESC techDesc = { 0 };
	pTech->GetDesc(&techDesc);
	for (UINT i = 0; i < techDesc.Passes; ++i)
	{
		pTech->GetPassByIndex(i)->Apply(0, m_pD3D11ImmediateContext);
		m_pD3D11ImmediateContext->DrawIndexed(m_sphere.indices.size(), 0, 0);
	}

	m_pSwapChain->Present(0, 0);

	return true;
}

void HrRenderD3D11DemoGeometry::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

bool HrRenderD3D11DemoGeometry::BuildHLSL()
{
	ifstream fxFile("Media/HrShader/BasicDraw.fxo", ios::binary);
	if (!fxFile)
	{
		return false;
	}

	fxFile.seekg(0, ifstream::end);
	UINT nSize = static_cast<UINT>(fxFile.tellg());
	fxFile.seekg(0, ifstream::beg);

	vector<char> shader(nSize);
	fxFile.read(&shader[0], nSize);
	fxFile.close();

	HRESULT rt = D3DX11CreateEffectFromMemory(&shader[0], nSize, 0, m_pD3D11Device, &m_pEffect);
	if (FAILED(rt))
	{
		HRERROR(_T("D3DX11CreateEffectFromMemory Error!"));
		return false;
	}

	m_pFxWorldViewProj = m_pEffect->GetVariableByName("g_worldViewProj")->AsMatrix();

	return true;
}

bool HrRenderD3D11DemoGeometry::BuildInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC iDesc[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	ID3DX11EffectTechnique *tech = m_pEffect->GetTechniqueByName("BasicDraw");
	D3DX11_PASS_DESC pDesc;
	tech->GetPassByIndex(0)->GetDesc(&pDesc);
	if (FAILED(m_pD3D11Device->CreateInputLayout(iDesc, 2, pDesc.pIAInputSignature, pDesc.IAInputSignatureSize, &m_pInputLayout)))
	{
		MessageBox(NULL, L"CreateInputLayout failed!", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool HrRenderD3D11DemoGeometry::BuildBuffers()
{
	//CreateGrid(5.0f, 5.0f, 2, 2, m_grid);
	CreateSphere(2, 30, 20, m_sphere);

	UINT nTotalVerts = m_sphere.vertices.size();
	UINT nTotalIndices = m_sphere.indices.size();

	vector<VertexPos> vertices(nTotalVerts);
	for (UINT i = 0; i < nTotalVerts; ++i)
	{
		vertices[i].pos = m_sphere.vertices[i].pos;
		vertices[i].color = XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	}
	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = nTotalVerts * sizeof(VertexPos);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.StructureByteStride = 0;
	vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA vbData;
	vbData.pSysMem = &vertices[0];
	vbData.SysMemPitch = 0;
	vbData.SysMemSlicePitch = 0;

	HRESULT rt = m_pD3D11Device->CreateBuffer(&vbDesc, &vbData, &m_pVertexBuffer);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateVertexBuffer Error!"));
		return false;
	}

	vector<UINT> indices(nTotalIndices);
	for (UINT i = 0; i < m_sphere.indices.size(); ++i)
	{
		indices[i] = m_sphere.indices[i];
	}
	D3D11_BUFFER_DESC ibDesc = { 0 };
	ibDesc.ByteWidth = nTotalIndices * sizeof(UINT);
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;
	ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA ibData;
	ibData.pSysMem = &indices[0];
	ibData.SysMemPitch = 0;
	ibData.SysMemSlicePitch = 0;

	rt = m_pD3D11Device->CreateBuffer(&ibDesc, &ibData, &m_pIndexBuffer);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateIndexBuffer Error!"));
		return false;
	}

	return true;
	
}

void HrRenderD3D11DemoGeometry::CreateBox(float width, float height, float depth, MeshData &mesh)
{
	mesh.vertices.clear();
	mesh.indices.clear();

	//一共24个顶点(每面4个)
	mesh.vertices.resize(24);
	//一共36个索引(每面6个)
	mesh.indices.resize(36);

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;
	float halfD = depth * 0.5f;

	//眼睛面向z轴正方向
	//构建顶点
	//前面
	mesh.vertices[0].pos = XMFLOAT3(-halfW, -halfH, -halfD);
	mesh.vertices[0].normal = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[0].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[0].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[1].pos = XMFLOAT3(-halfW, halfH, -halfD);
	mesh.vertices[1].normal = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[1].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[1].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[2].pos = XMFLOAT3(halfW, halfH, -halfD);
	mesh.vertices[2].normal = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[2].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[2].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[3].pos = XMFLOAT3(halfW, -halfH, -halfD);
	mesh.vertices[3].normal = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[3].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[3].tex = XMFLOAT2(1.f, 1.f);
	//左侧面
	mesh.vertices[4].pos = XMFLOAT3(-halfW, -halfH, halfD);
	mesh.vertices[4].normal = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[4].tangent = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[4].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[5].pos = XMFLOAT3(-halfW, halfH, halfD);
	mesh.vertices[5].normal = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[5].tangent = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[5].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[6].pos = XMFLOAT3(-halfW, halfH, -halfD);
	mesh.vertices[6].normal = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[6].tangent = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[6].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[7].pos = XMFLOAT3(-halfW, -halfH, -halfD);
	mesh.vertices[7].normal = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[7].tangent = XMFLOAT3(0.f, 0.f, -1.f);
	mesh.vertices[7].tex = XMFLOAT2(1.f, 1.f);
	//背面
	mesh.vertices[8].pos = XMFLOAT3(halfW, -halfH, halfD);
	mesh.vertices[8].normal = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[8].tangent = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[8].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[9].pos = XMFLOAT3(halfW, halfH, halfD);
	mesh.vertices[9].normal = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[9].tangent = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[9].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[10].pos = XMFLOAT3(-halfW, halfH, halfD);
	mesh.vertices[10].normal = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[10].tangent = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[10].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[11].pos = XMFLOAT3(-halfW, -halfH, halfD);
	mesh.vertices[11].normal = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[11].tangent = XMFLOAT3(-1.f, 0.f, 0.f);
	mesh.vertices[11].tex = XMFLOAT2(1.f, 1.f);
	//右侧面
	mesh.vertices[12].pos = XMFLOAT3(halfW, -halfH, -halfD);
	mesh.vertices[12].normal = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[12].tangent = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[12].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[13].pos = XMFLOAT3(halfW, halfH, -halfD);
	mesh.vertices[13].normal = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[13].tangent = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[13].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[14].pos = XMFLOAT3(halfW, halfH, halfD);
	mesh.vertices[14].normal = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[14].tangent = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[14].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[15].pos = XMFLOAT3(halfW, -halfH, halfD);
	mesh.vertices[15].normal = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[15].tangent = XMFLOAT3(0.f, 0.f, 1.f);
	mesh.vertices[15].tex = XMFLOAT2(1.f, 1.f);
	//上面
	mesh.vertices[16].pos = XMFLOAT3(-halfW, halfH, -halfD);
	mesh.vertices[16].normal = XMFLOAT3(0.f, 1.f, 0.f);
	mesh.vertices[16].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[16].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[17].pos = XMFLOAT3(-halfW, halfH, halfD);
	mesh.vertices[17].normal = XMFLOAT3(0.f, 1.f, 0.f);
	mesh.vertices[17].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[17].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[18].pos = XMFLOAT3(halfW, halfH, halfD);
	mesh.vertices[18].normal = XMFLOAT3(0.f, 1.f, 0.f);
	mesh.vertices[18].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[18].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[19].pos = XMFLOAT3(halfW, halfH, -halfD);
	mesh.vertices[19].normal = XMFLOAT3(0.f, 1.f, 0.f);
	mesh.vertices[19].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[19].tex = XMFLOAT2(1.f, 1.f);
	//底面
	mesh.vertices[20].pos = XMFLOAT3(-halfW, -halfH, halfD);
	mesh.vertices[20].normal = XMFLOAT3(0.f, -1.f, 0.f);
	mesh.vertices[20].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[20].tex = XMFLOAT2(0.f, 1.f);
	mesh.vertices[21].pos = XMFLOAT3(-halfW, -halfH, -halfD);
	mesh.vertices[21].normal = XMFLOAT3(0.f, -1.f, 0.f);
	mesh.vertices[21].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[21].tex = XMFLOAT2(0.f, 0.f);
	mesh.vertices[22].pos = XMFLOAT3(halfW, -halfH, -halfD);
	mesh.vertices[22].normal = XMFLOAT3(0.f, -1.f, 0.f);
	mesh.vertices[22].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[22].tex = XMFLOAT2(1.f, 0.f);
	mesh.vertices[23].pos = XMFLOAT3(halfW, -halfH, halfD);
	mesh.vertices[23].normal = XMFLOAT3(0.f, -1.f, 0.f);
	mesh.vertices[23].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[23].tex = XMFLOAT2(1.f, 1.f);

	//构建索引
	mesh.indices[0] = 0;
	mesh.indices[1] = 1;
	mesh.indices[2] = 2;
	mesh.indices[3] = 0;
	mesh.indices[4] = 2;
	mesh.indices[5] = 3;

	mesh.indices[6] = 4;
	mesh.indices[7] = 5;
	mesh.indices[8] = 6;
	mesh.indices[9] = 4;
	mesh.indices[10] = 6;
	mesh.indices[11] = 7;

	mesh.indices[12] = 8;
	mesh.indices[13] = 9;
	mesh.indices[14] = 10;
	mesh.indices[15] = 8;
	mesh.indices[16] = 10;
	mesh.indices[17] = 11;

	mesh.indices[18] = 12;
	mesh.indices[19] = 13;
	mesh.indices[20] = 14;
	mesh.indices[21] = 12;
	mesh.indices[22] = 14;
	mesh.indices[23] = 15;

	mesh.indices[24] = 16;
	mesh.indices[25] = 17;
	mesh.indices[26] = 18;
	mesh.indices[27] = 16;
	mesh.indices[28] = 18;
	mesh.indices[29] = 19;

	mesh.indices[30] = 20;
	mesh.indices[31] = 21;
	mesh.indices[32] = 22;
	mesh.indices[33] = 20;
	mesh.indices[34] = 22;
	mesh.indices[35] = 23;
}

void HrRenderD3D11DemoGeometry::CreateGrid(float fWidth, float fHeight, UINT m, UINT n, MeshData &mesh)
{
	mesh.vertices.clear();
	mesh.indices.clear();

	uint32 nVertsRow = m + 1;
	uint32 nVertsCol = n + 1;

	float fStartX = -fWidth * 0.5f;
	float fStartZ = fHeight * 0.5f;

	float fDisWidth = fWidth / m;
	float fDisHeight = fHeight / n;

	uint32 nVertexs = nVertsRow * nVertsCol;
	mesh.vertices.resize(nVertexs);
	for (UINT nRowIndex = 0; nRowIndex < nVertsRow; ++nRowIndex)
	{
		for (UINT nColIndex = 0; nColIndex < nVertsCol; ++nColIndex)
		{
			uint32 nVertexIndex = nRowIndex * nVertsCol + nColIndex;
			mesh.vertices[nVertexIndex].pos.x = fStartX + nColIndex * fDisWidth;
			mesh.vertices[nVertexIndex].pos.y = 0.0f;
			mesh.vertices[nVertexIndex].pos.z = fStartZ - nRowIndex * fDisHeight;

			mesh.vertices[nVertexIndex].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			mesh.vertices[nVertexIndex].tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);
			mesh.vertices[nVertexIndex].tex = XMFLOAT2(nRowIndex * fDisWidth, nColIndex * fDisHeight);
		}
	}

	uint32 nIndices = m * n * 6;
	mesh.indices.resize(nIndices);
	uint32 nIndicesIndex = 0;

	for (UINT nRowIndex = 0; nRowIndex < nVertsRow-1; ++nRowIndex)
	{
		for (UINT nColIndex = 0; nColIndex < nVertsCol-1; ++nColIndex)
		{
			mesh.indices[nIndicesIndex] = nRowIndex * nVertsCol + nColIndex;
			mesh.indices[nIndicesIndex + 1] = nRowIndex * nVertsCol + nColIndex + 1;
			mesh.indices[nIndicesIndex + 2] = (nRowIndex + 1) * nVertsCol + nColIndex;
			mesh.indices[nIndicesIndex + 3] = nRowIndex * nVertsCol + nColIndex + 1;
			mesh.indices[nIndicesIndex + 4] = (nRowIndex + 1) * nVertsCol + nColIndex + 1;
			mesh.indices[nIndicesIndex + 5] = (nRowIndex + 1) * nVertsCol + nColIndex;

			nIndicesIndex += 6;
		}
	}
}

void HrRenderD3D11DemoGeometry::CreateSphere(float radius, int slice, int stack, MeshData &mesh)
{
	mesh.vertices.clear();
	mesh.indices.clear();

	int vertsPerRow = slice + 1;
	int nRows = stack - 1;

	int nVerts = vertsPerRow * nRows + 2;
	int nIndices = (nRows - 1)*slice * 6 + slice * 6;

	mesh.vertices.resize(nVerts);
	mesh.indices.resize(nIndices);

	for (int i = 1; i <= nRows; ++i)
	{
		float phy = XM_PI * i / stack;
		float tmpRadius = radius * sin(phy);
		for (int j = 0; j < vertsPerRow; ++j)
		{
			float theta = XM_2PI * j / slice;
			UINT index = (i - 1)*vertsPerRow + j;

			float x = tmpRadius*cos(theta);
			float y = radius*cos(phy);
			float z = tmpRadius*sin(theta);

			//位置坐标
			mesh.vertices[index].pos = XMFLOAT3(x, y, z);
			//法线
			XMVECTOR N = XMVectorSet(x, y, z, 0.f);
			XMStoreFloat3(&mesh.vertices[index].normal, XMVector3Normalize(N));
			//切线
			XMVECTOR T = XMVectorSet(-sin(theta), 0.f, cos(theta), 0.f);
			XMStoreFloat3(&mesh.vertices[index].tangent, XMVector3Normalize(T));
			//纹理坐标
			mesh.vertices[index].tex = XMFLOAT2(j*1.f / slice, i*1.f / stack);
		}
	}

	int size = vertsPerRow * nRows;
	//添加顶部和底部两个顶点信息
	mesh.vertices[size].pos = XMFLOAT3(0.f, radius, 0.f);
	mesh.vertices[size].normal = XMFLOAT3(0.f, 1.f, 0.f);
	mesh.vertices[size].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[size].tex = XMFLOAT2(0.f, 0.f);

	mesh.vertices[size + 1].pos = XMFLOAT3(0.f, -radius, 0.f);
	mesh.vertices[size + 1].normal = XMFLOAT3(0.f, -1.f, 0.f);
	mesh.vertices[size + 1].tangent = XMFLOAT3(1.f, 0.f, 0.f);
	mesh.vertices[size + 1].tex = XMFLOAT2(0.f, 1.f);

	UINT tmp(0);
	int start1 = 0;
	int start2 = mesh.vertices.size() - vertsPerRow - 2;
	int top = size;
	int bottom = size + 1;
	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = top;
		mesh.indices[tmp + 1] = start1 + i + 1;
		mesh.indices[tmp + 2] = start1 + i;

		tmp += 3;
	}

	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = bottom;
		mesh.indices[tmp + 1] = start2 + i;
		mesh.indices[tmp + 2] = start2 + i + 1;

		tmp += 3;
	}

	for (int i = 0; i < nRows - 1; ++i)
	{
		for (int j = 0; j < slice; ++j)
		{
			mesh.indices[tmp] = i * vertsPerRow + j;
			mesh.indices[tmp + 1] = (i + 1) * vertsPerRow + j + 1;
			mesh.indices[tmp + 2] = (i + 1) * vertsPerRow + j;
			mesh.indices[tmp + 3] = i * vertsPerRow + j;
			mesh.indices[tmp + 4] = i * vertsPerRow + j + 1;
			mesh.indices[tmp + 5] = (i + 1) * vertsPerRow + j + 1;

			tmp += 6;
		}
	}
}

