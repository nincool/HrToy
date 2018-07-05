#ifndef _HR_D3D11DEPTHSTENCIL_H_
#define _HR_D3D11DEPTHSTENCIL_H_

#include "HrRenderSystem/HrRenderCommon/HrRenderPreDeclare.h"
#include "HrCore/Include/Render/HrDepthStencil.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11DepthStencil : public HrDepthStencil
	{
	public:
		HrD3D11DepthStencil(uint32 nWidth, uint32 nHeight, EnumPixelFormat format, uint32 texD3DUsage);
		virtual ~HrD3D11DepthStencil();

		virtual HrTexturePtr GetDepthStencilSRV() override;

		const ID3D11DepthStencilViewPtr& GetDepthStencilView();
		const ID3D11ShaderResourceViewPtr& GetDepthStencilShaderResouceView();
	private:
		bool CreateDepthStencilView();
	private:
		HrD3D11Texture2DPtr m_pTexDepthStencilView;
		uint32 m_texD3DUsage;
	};

}

#endif
