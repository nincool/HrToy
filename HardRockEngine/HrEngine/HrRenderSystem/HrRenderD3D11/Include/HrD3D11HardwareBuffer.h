#ifndef _HR_D3D11HARDWAREBUFFER_H_
#define _HR_D3D11HARDWAREBUFFER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrHardwareBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11HardwareBuffer : public HrHardwareBuffer
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
		HrD3D11HardwareBuffer(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pImmediateContext);
		HrD3D11HardwareBuffer(HrD3D11HardwareBuffer& hardwareBuffer);
		HrD3D11HardwareBuffer(HrD3D11HardwareBuffer&& hardwardBuffer);
		virtual ~HrD3D11HardwareBuffer();

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrGraphicsBuffer::EnumHardwareBufferBind bindFlag) override;
		
		ID3D11Buffer* GetGraphicsBuffer();
	private:
		void CreateHardwareBuffer(const void* pResourceData);
		void GetD3DBufferDesc(D3D11_USAGE& usage, UINT& cpuAccessFlags, UINT& bindFlags, UINT& miscFlags);
	private:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11Buffer* m_pD3D11Buffer;
	};
}

#endif




