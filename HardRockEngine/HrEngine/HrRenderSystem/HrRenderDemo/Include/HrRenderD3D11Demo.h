#ifndef _HR_RENDERD3D11DEMO_H_
#define _HR_RENDERD3D11DEMO_H_

#include "IRenderDemo.h"
#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_RENDERDEMO_API HrRenderD3D11Demo : public IRenderDemo, public RenderSysAllocatedObject
	{
	public:
		HrRenderD3D11Demo();

		virtual void SetD3DDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContex) override;

		virtual bool Init() override;
		virtual bool Render() override;
		virtual void Release() override;

	private:
		bool LoadContent();
		bool CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer);
	protected:
		HR_SYNTHESIZE_READONLY(ID3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE_READONLY(ID3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);

		struct VertexPos
		{
			DirectX::XMFLOAT3 pos;
		};


		ID3D11VertexShader* m_pSolidColorVS;
		ID3D11PixelShader* m_pSolidColorPS;

		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;


	};
}

#endif