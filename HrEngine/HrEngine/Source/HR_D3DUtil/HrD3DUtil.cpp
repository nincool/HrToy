#include "HrDefine.h"
#include "HrD3DUtil.h"

using namespace HR;

LPDIRECT3D9 CHrD3DUtil::m_s_pD3D = NULL;
LPDIRECT3DDEVICE9 CHrD3DUtil::m_s_pD3DDevice = NULL;

D3DXCOLOR CHrD3DUtil::WHITE = D3DCOLOR_XRGB(255, 255, 255);
D3DXCOLOR CHrD3DUtil::BLACK = D3DCOLOR_XRGB(0, 0, 0);
D3DXCOLOR CHrD3DUtil::RED = D3DCOLOR_XRGB(255, 0, 0);
D3DXCOLOR CHrD3DUtil::GREEN = D3DCOLOR_XRGB(0, 255, 0);
D3DXCOLOR CHrD3DUtil::BLUE = D3DCOLOR_XRGB(0, 0, 255);
D3DXCOLOR CHrD3DUtil::YELLOW = D3DCOLOR_XRGB(255, 255, 0);
D3DXCOLOR CHrD3DUtil::CYAN = D3DCOLOR_XRGB(0, 255, 255);
D3DXCOLOR CHrD3DUtil::MAGENTA = D3DCOLOR_XRGB(255, 0, 255);

D3DXCOLOR CHrD3DUtil::BEACH_SAND = D3DCOLOR_XRGB(255, 249, 157);
D3DXCOLOR CHrD3DUtil::DESERT_SAND = D3DCOLOR_XRGB(250, 205, 135);

D3DXCOLOR CHrD3DUtil::LIGHTGREEN = D3DCOLOR_XRGB(60, 184, 120);
D3DXCOLOR CHrD3DUtil::PUREGREEN = D3DCOLOR_XRGB(0, 166, 81);
D3DXCOLOR CHrD3DUtil::DARKGREEN = D3DCOLOR_XRGB(0, 114, 54);

D3DXCOLOR CHrD3DUtil::LIGHT_YELLOW_GREEN = D3DCOLOR_XRGB(124, 197, 118);
D3DXCOLOR CHrD3DUtil::PURE_YELLOW_GREEN = D3DCOLOR_XRGB(57, 181, 74);
D3DXCOLOR CHrD3DUtil::DARK_YELLOW_GREEN = D3DCOLOR_XRGB(25, 123, 48);

D3DXCOLOR CHrD3DUtil::LIGHTBROWN = D3DCOLOR_XRGB(198, 156, 109);
D3DXCOLOR CHrD3DUtil::DARKBROWN = D3DCOLOR_XRGB(115, 100, 87);

float CHrD3DUtil::INFINITYFLOAT = FLT_MAX;

CHrD3DUtil::CHrD3DUtil(void)
{
}


CHrD3DUtil::~CHrD3DUtil(void)
{
}

bool CHrD3DUtil::InitializeD3D( const HWND& hWnd, int nWidth, int nHeight, bool bFullScreenm, D3DDEVTYPE deviceType )
{
	m_s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_s_pD3D == NULL)
	{
		return false;
	}
	D3DDISPLAYMODE displayMode;
	if (FAILED(m_s_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
	{
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	D3DCAPS9 d3dCaps;
	m_s_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &d3dCaps);
	int nVp = 0;
	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (!bFullScreenm)
	{
		d3dpp.Windowed = true;
	}
	else
	{
		d3dpp.Windowed = false;
	}
	d3dpp.BackBufferWidth = nWidth;
	d3dpp.BackBufferHeight = nHeight;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = displayMode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_s_pD3D->CreateDevice(D3DADAPTER_DEFAULT
		, deviceType
		, hWnd
		, nVp
		, &d3dpp
		, &m_s_pD3DDevice)))
	{
		return false;
	}

	return true;
}



bool CHrD3DUtil::ReleaseD3D()
{
	SAFE_RELEASE(m_s_pD3D);
	SAFE_RELEASE(m_s_pD3DDevice);

	return true;
}

IDirect3DDevice9* CHrD3DUtil::GetD3DDevice()
{
	return m_s_pD3DDevice;
}

int CHrD3DUtil::GetMaxAnisotropy()
{
	D3DCAPS9 stCaps;
	::ZeroMemory(&stCaps, sizeof(stCaps));

	if (m_s_pD3DDevice != NULL)
		m_s_pD3DDevice->GetDeviceCaps(&stCaps);
	int nMaxAnisotropy = stCaps.MaxAnisotropy;

	return nMaxAnisotropy;

}

void CHrD3DUtil::SetSamplerPoint()
{
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 16);
}

void CHrD3DUtil::SetSamplerLiner()
{
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 16);
}

void CHrD3DUtil::SetSamplerAnisotropy()
{
	int nMaxAnisotropy = GetMaxAnisotropy();
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, nMaxAnisotropy);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_s_pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 16);
}

void CHrD3DUtil::SetNormalTextureRender()
{
	//使用纹理坐标
	m_s_pD3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//设置颜色来源 纹理
	m_s_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//使用当前颜色作为第一个texture stage的输出
	m_s_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
}
