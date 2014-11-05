#include "HrTexture.h"

using namespace HR;
CHrTexture::CHrTexture()
{
	m_pTexture = NULL;
	m_pD3DDevice = NULL;
}


CHrTexture::~CHrTexture()
{
	SAFE_RELEASE(m_pTexture);
}

void CHrTexture::Initialize(IDirect3DDevice9* pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

bool CHrTexture::LoadTexture(char* pTextureFile, bool bCreateMipmap)
{
	if (bCreateMipmap)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(m_pD3DDevice, pTextureFile, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0x00, NULL, NULL, &m_pTexture)))
		{
			return false;
		}

		return true;
	}
	else
	{
		if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, pTextureFile, &m_pTexture)))
		{
			return false;
		}
		return true;
	}
}

IDirect3DTexture9* CHrTexture::GetTexture()
{
	return m_pTexture;
}
