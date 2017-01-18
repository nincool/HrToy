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
		/// Enums describing buffer usage; not mutually exclusive
		enum EnumTextureUsage
		{
			TU_GPUREAD_GPUWRITE,
			TU_GPUREAD_CPUWRITE,
			TU_GPUREAD_IMMUTABLE,
			TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};
	public:
		HrD3D11Texture(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext
			, EnumTextureType texType
			, uint32 nSampleCount
			, uint32 nSampleQuality);
		~HrD3D11Texture();

		ID3D11Resource* GetD3DResource() const { return m_pD3DResource; }
		ID3D11ShaderResourceView* GetD3D11SRV() const { return m_pD3DSRV; }

	protected:
		virtual void CreateTexture() override;
		virtual void CreateSRV() override;
	protected:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;
		ID3D11Resource* m_pD3DResource;

		ID3D11ShaderResourceView* m_pD3DSRV;

	};

	class HrD3D11Texture2D : public HrD3D11Texture
	{
	public:
		HrD3D11Texture2D(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext
			, EnumTextureType texType
			, uint32 nSampleCount
			, uint32 nSampleQuality);
		~HrD3D11Texture2D();

	protected:
		virtual void CreateTexture() override;
		virtual void CreateSRV() override;

	protected:
		ID3D11Texture2D* m_pD3DTexture2D;
	};
}


#endif



