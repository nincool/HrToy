#ifndef _I_RENDERDEMO_H_
#define _I_RENDERDEMO_H_

#include "HrRenderDemoPrerequisites.h"
#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include <D3Dcompiler.h>

namespace Hr
{
	class HR_RENDERDEMO_API IRenderDemo : public RenderSysAllocatedObject
	{
	public:
		~IRenderDemo(){}

		virtual void SetD3DDevice(ID3D11Device* pDevice
			, ID3D11DeviceContext* pDeviceContex
			, ID3D11RenderTargetView* pRenderTargetView
			, ID3D11DepthStencilView* pDepthStencilView
			, IDXGISwapChain* pSwapChain) = 0;

		virtual bool Init() = 0;

		virtual bool Render() = 0;

		virtual void Release() = 0;

	public:
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
					//char* pMsg = (char*)(errorBuffer->GetBufferPointer());
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