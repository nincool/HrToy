#ifndef _HR_RENDERD3D11DEMOPIPLELINE_H_
#define _HR_RENDERD3D11DEMOPIPLELINE_H_

#include "IRenderDemo.h"

using namespace DirectX;

class ID3DX11Effect;
class ID3DX11EffectMatrixVariable;
namespace Hr
{
	class HR_RENDERDEMO_API HrRenderD3D11DemoPipleline : public IRenderDemo
	{
	public:
		HrRenderD3D11DemoPipleline();

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

		struct Vertex
		{
			XMFLOAT3 pos;
			XMFLOAT4 color;
		};

		ID3DX11Effect* m_pEffect;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		ID3DX11EffectMatrixVariable* m_pFxWorldViewProj;

		//���������
		HrCameraPtr m_pShareCamera;
	};
}

#endif


