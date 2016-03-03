#include "HrRenderD3D11DemoHLSL.h"
#include <fstream>


using namespace Hr;
using namespace DirectX;
using namespace std;

HrRenderD3D11DemoHLSL::HrRenderD3D11DemoHLSL()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_pSwapChain = nullptr;

	m_pSolidColorVS = nullptr;
	m_pSolidColorPS = nullptr;

	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;

	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
}

void HrRenderD3D11DemoHLSL::SetD3DDevice(ID3D11Device* pDevice
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

bool HrRenderD3D11DemoHLSL::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoHLSL::Render()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//unsigned int stride = sizeof(VertexPos);
	//unsigned int offset = 0;

	//m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);
	//m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	//m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//m_pD3D11ImmediateContext->VSSetShader(m_pSolidColorVS, 0, 0);
	//m_pD3D11ImmediateContext->PSSetShader(m_pSolidColorPS, 0, 0);
	//m_pD3D11ImmediateContext->Draw(3, 0);

	m_pSwapChain->Present(0, 0);

	return true;
}


void HrRenderD3D11DemoHLSL::Release()
{

	SAFE_RELEASE(m_pSolidColorVS);
	SAFE_RELEASE(m_pSolidColorPS);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexBuffer);
}

bool HrRenderD3D11DemoHLSL::LoadContent()
{
	ID3DBlob* pMicroCode;
	ID3DBlob* pErrorMsg;

	std::string strSource;
	std::fstream fxFile("Media\\HrShader\\BasicDraw.fx", ios::in | ios::ate);
	uint32 nFileLength = fxFile.tellg();
	fxFile.seekg(0, ios::beg);
	strSource.resize(nFileLength+1);
	fxFile.read((char*)strSource.c_str(), nFileLength);

	HRESULT hr = D3DCompile(
		strSource.c_str(),
		strSource.size(),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		"fx_5_0",
		0,
		NULL,
		&pMicroCode,
		&pErrorMsg
		);





	return true;
}

