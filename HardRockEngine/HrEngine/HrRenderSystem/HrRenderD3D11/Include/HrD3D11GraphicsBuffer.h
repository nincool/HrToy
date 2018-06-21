#ifndef _HR_D3D11GRAPHICSBUFFER_H_
#define _HR_D3D11GRAPHICSBUFFER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11GraphicsBuffer : public HrGraphicsBuffer
	{
//Resource Usage Flags(D3D11_USAGE)
//		                    GPU-Read                  GPU-Write                 CPU-Read                  CPU-Write
//
//Default                     yes                       yes
//
//Dynamic                     yes                                                                            yes
//
//Immutable                   yes
//
//Staging                     yes                       yes                       yes                        yes
	public:
		HrD3D11GraphicsBuffer(const ID3D11DevicePtr& pD3D11Device, const ID3D11DeviceContextPtr& pImmediateContext);
		HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer& hardwareBuffer);
		HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer&& hardwardBuffer);
		virtual ~HrD3D11GraphicsBuffer();

		virtual void BindStream(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag) override;
		
		const ID3D11BufferPtr& GetD3DGraphicsBuffer();

	private:
		virtual void* Map(HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag) override;
		virtual void Unmap() override;

		void CreateHardwareBuffer(const void* pResourceData);
		
	private:
		ID3D11DevicePtr m_pD3D11Device;
		ID3D11DeviceContextPtr m_pImmediateContext;

		ID3D11BufferPtr m_pD3D11Buffer;
		//ID3D11ShaderResourceViewPtr m_pSRV;
	};
}

#endif




