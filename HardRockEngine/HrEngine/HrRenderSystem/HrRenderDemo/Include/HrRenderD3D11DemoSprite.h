#ifndef _HR_RENDERD3D11DEMOSPRITE_H_
#define _HR_RENDERD3D11DEMOSPRITE_H_

#include "HrRenderDemoPrerequisites.h"
#include "IRenderDemo.h"

namespace DirectX
{
	class SpriteBatch;
}


namespace Hr
{
	class HR_RENDERDEMO_API HrRenderD3D11DemoSprite : public IRenderDemo
	{
	public:
		HrRenderD3D11DemoSprite();

		virtual void SetD3DDevice(ID3D11Device* pDevice
			, ID3D11DeviceContext* pDeviceContex
			, ID3D11RenderTargetView* pRenderTargetView
			, ID3D11DepthStencilView* pDepthStencilView
			, IDXGISwapChain* pSwapChain) override;

		virtual bool Init() override;
		virtual bool Render() override;
		virtual void Release() override;

	private:
		bool LoadContent();

	protected:
		HR_SYNTHESIZE_READONLY(ID3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE_READONLY(ID3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);
		HR_SYNTHESIZE(IDXGISwapChain*, m_pSwapChain, SwapChain);

		HR_SYNTHESIZE(ID3D11RenderTargetView*, m_pRenderTargetView, RenderTargetView);
		HR_SYNTHESIZE(ID3D11DepthStencilView*, m_pDepthStencilView, DepthStencilView);

		struct VertexPos
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT2 tex0;
		};

		ID3D11VertexShader* m_pSolidColorVS;
		ID3D11PixelShader* m_pSolidColorPS;

		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pConstBuffer;

		ID3D11ShaderResourceView* m_pColorMap;
		
		ID3D11Resource* m_pTexture;

		ID3D11BlendState* m_pAlphaBlendState;
		ID3D11DepthStencilState* m_pDepthStencilState;
		ID3D11RasterizerState* m_pRasterizerState;
		ID3D11SamplerState* m_pColorMapSampler;

		

		DirectX::SpriteBatch* m_pSprite1;
	};
}

#endif


