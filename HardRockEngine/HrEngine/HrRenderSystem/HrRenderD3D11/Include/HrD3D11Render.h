#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/IRender.h"

struct ID3D11DeviceContext;
struct ID3D11Device;

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "DirectXFX11/inc/d3dx11effect.h"
#include "HrCore/Include/HrLog.h"
#include <D3Dcompiler.h>

struct ID3DX11EffectMatrixVariable;

namespace Hr
{
	class HrD3D11Device;
	class IRenderDemo;

	class HrD3D11Render : public IRender
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
		virtual void Release() override;
		virtual bool StartRender() override;

		//Testing 
		bool LoadContent();
		bool TestRender(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout);
	public:
		virtual void Render(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout) override;

	private:
		HR_SYNTHESIZE_READONLY(ID3D11Device*, m_pD3D11Device, D3D11Device);
		HR_SYNTHESIZE_READONLY(ID3D11DeviceContext*, m_pD3D11ImmediateContext, D3D11ImmediateContext);

		/////////////////////////////--- RenderTest ---/////////////////////////////////
	public:
		IRenderDemo* m_pRenderDemo;

		HR_SYNTHESIZE_READONLY(HrD3D11RenderWindowPtr, m_pShareRenderWindow, RenderWindow);


		//Testing
		ID3DX11EffectMatrixVariable* m_pFxWorldViewProj;

		//测试摄像机
		HrCameraPtr m_pShareCamera;

		//Testing
		ID3DX11Effect* m_pEffect;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		ID3D11VertexShader* m_pSolidColorVS;
		ID3D11PixelShader* m_pSolidColorPS;
		bool CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer)
		{
			DWORD shaderFlags = 0;//D3DCOMPILE_ENABLE_STRICTNESS;

			ID3DBlob* errorBuffer = 0;
			HRESULT result;

			result = D3DCompileFromFile(pFilePath, 0, 0, pEntry, pTarget,
				shaderFlags, 0, pBuffer, &errorBuffer);
			if (FAILED(result))
			{
				if (errorBuffer != 0)
				{
					char* pMsg = (char*)(errorBuffer->GetBufferPointer());
					HRERROR((LPCWSTR)errorBuffer->GetBufferPointer());
					errorBuffer->Release();
				}
				HRERROR(_T("CompileD3DShader Error! File[%s]"), pFilePath);
				return false;
			}

			if (errorBuffer != 0)
				errorBuffer->Release();

			return true;
		}

	};
}


#endif

