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
		HrD3D11Texture(EnumTextureType texType
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor);

		~HrD3D11Texture();

		const ID3D11RenderTargetViewPtr& GetD3DRenderTargetView();
		const ID3D11DepthStencilViewPtr& GetD3DDepthStencilView();
		const ID3D11ShaderResourceViewPtr& GetD3D11ShaderResourceView();

		const ID3D11ResourcePtr& GetD3D11Resource();

	protected:
		UINT GetD3DTextureBindFlags();
		UINT GetD3DCPUAccessFlags();
	protected:
		ID3D11DevicePtr m_pD3D11Device;
		ID3D11DeviceContextPtr m_pD3D11Context;

		ID3D11ResourcePtr m_pD3DResource;

		ID3D11RenderTargetViewPtr m_pRenderTargetView;
		ID3D11DepthStencilViewPtr m_pDepthStencilView;
		ID3D11ShaderResourceViewPtr m_pShaderResourceView;
	};

	/////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////

	class HrD3D11Texture2D : public HrD3D11Texture
	{
	public:
		HrD3D11Texture2D(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor = TUF_TEX_DEFAULTTEXTURE
			, EnumPixelFormat format = PF_R8G8B8A8);
		HrD3D11Texture2D(const ID3D11Texture2DPtr& pD3DTex2D, EnumTextureUsedFor texUsedFor);

		~HrD3D11Texture2D();

		virtual void CreateHWResource(std::vector<std::shared_ptr<HrImage> >& vecImage) override;
		
		ID3D11Texture2DPtr GetD3D11Texture();

	private:
		bool CreateRenderTargetView();
		bool CreateDepthStencilView();
		bool CreateShaderResourceView();
	protected:
		ID3D11Texture2DPtr m_pD3D11Texture2D;
	};

	/////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////

	class HrD3D11TextureCubeMap : public HrD3D11Texture
	{
	public:
		HrD3D11TextureCubeMap(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor
			, EnumPixelFormat format);

		virtual void CreateHWResource(std::vector<std::shared_ptr<HrImage> >& vecImage) override;
	protected:
		bool CreateShaderResourceView();

	protected:
		ID3D11Texture2DPtr m_pD3D11Texture2D;
	};
}


#endif



