#ifndef _HR_D3D11TEXTURE_H_
#define _HR_D3D11TEXTURE_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Asset/HrTexture.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"


namespace Hr
{
	class HrD3D11Texture : public HrTexture
	{
	public:
		enum EnumD3DTEXTURE_USED
		{
			D3D_TEX_RENDERTARGETVIEW,
			D3D_TEX_DEPTHSTENCILVIEW,
		};
	public:
		HrD3D11Texture(EnumTextureType texType
			, uint32 nWidth
			, uint32 nHeight
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, EnumD3DTEXTURE_USED texUsage);

		~HrD3D11Texture();

		const ID3D11RenderTargetViewPtr& GetD3DRenderTargetView();
		const ID3D11DepthStencilViewPtr& GetD3DDepthStencilView();

		const ID3D11ResourcePtr& GetD3D11Resource();
	protected:
		ID3D11DevicePtr m_pD3D11Device;
		ID3D11DeviceContextPtr m_pD3D11Context;

		EnumD3DTEXTURE_USED m_texUsage;

		ID3D11ResourcePtr m_pD3DTexture;

		ID3D11RenderTargetViewPtr m_pRenderTargetView;
		ID3D11DepthStencilViewPtr m_pDepthStencilView;
	};

	class HrD3D11Texture2D : public HrD3D11Texture
	{
	public:
		HrD3D11Texture2D(uint32 nWidth
			, uint32 nHeight
			, EnumD3DTEXTURE_USED texUsage);
		HrD3D11Texture2D( uint32 nWidth
			, uint32 nHeight
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, EnumD3DTEXTURE_USED texUsage);
		HrD3D11Texture2D(const ID3D11Texture2DPtr& pD3DTex2D, EnumD3DTEXTURE_USED texUsage);

		~HrD3D11Texture2D();

	protected:
		bool CreateRenderTargetView();
		bool CreateDepthStencilView();
	protected:
	
	};
}


#endif



