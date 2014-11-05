#ifndef _HR_D3DUTIL_H_
#define _HR_D3DUTIL_H_

#include <d3dx9.h>

namespace HR
{
	class CHrD3DUtil
	{
	public:
		CHrD3DUtil(void);
		~CHrD3DUtil(void);

	public:
		static bool               InitializeD3D(const HWND& hWnd, int nWidth, int nHeight, bool bFullScreenm, D3DDEVTYPE deviceType);
		static bool               ReleaseD3D();

		static IDirect3DDevice9*  GetD3DDevice();

	public:
		/////////////////////////-- texture --////////////////////////
		/**
		 *	@Brief: 获取设备支持的各向异性取值范围 [7/25/2014 By Hr]
		*/
		static int                GetMaxAnisotropy();

		static void               SetSamplerPoint();
		static void               SetSamplerLiner();
		static void               SetSamplerAnisotropy();

		static void               SetNormalTextureRender();

	public:
		static D3DXCOLOR        WHITE;
		static D3DXCOLOR        BLACK;
		static D3DXCOLOR        RED;
		static D3DXCOLOR        GREEN;
		static D3DXCOLOR        BLUE;
		static D3DXCOLOR        YELLOW;
		static D3DXCOLOR        CYAN;
		static D3DXCOLOR        MAGENTA;

		static D3DXCOLOR        BEACH_SAND;
		static D3DXCOLOR        DESERT_SAND;

		static D3DXCOLOR        LIGHTGREEN;
		static D3DXCOLOR        PUREGREEN;
		static D3DXCOLOR        DARKGREEN;

		static D3DXCOLOR        LIGHT_YELLOW_GREEN;
		static D3DXCOLOR        PURE_YELLOW_GREEN;
		static D3DXCOLOR        DARK_YELLOW_GREEN;

		static D3DXCOLOR        LIGHTBROWN;
		static D3DXCOLOR        DARKBROWN;


		static float            INFINITYFLOAT;

	private:
		static LPDIRECT3D9        m_s_pD3D;
		static LPDIRECT3DDEVICE9  m_s_pD3DDevice;

	};
}

#endif

