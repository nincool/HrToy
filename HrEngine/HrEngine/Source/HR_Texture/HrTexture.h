#ifndef _HR_TEXTURE_H_
#define _HR_TEXTURE_H_

#include "HrCommon.h"

namespace HR
{
	class CHrTexture
	{
	public:
		CHrTexture();
		~CHrTexture();

	public:
		void               Initialize(IDirect3DDevice9* pD3DDevice);
		bool               LoadTexture(char* pTextureFile, bool bCreateMipmap);

		IDirect3DTexture9* GetTexture();
	private:
		IDirect3DDevice9*  m_pD3DDevice;
		IDirect3DTexture9* m_pTexture;
	};
}

#endif


