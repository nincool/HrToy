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
		HrD3D11GraphicsBuffer(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pImmediateContext);
		HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer& hardwareBuffer);
		HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer&& hardwardBuffer);
		virtual ~HrD3D11GraphicsBuffer();

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag) override;
		
		ID3D11Buffer* GetGraphicsBuffer();

	private:
		virtual void* Map(HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag) override;
		virtual void Unmap() override;

		void CreateHardwareBuffer(const void* pResourceData);
		
	private:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11Buffer* m_pD3D11Buffer;
	};
}

#endif




