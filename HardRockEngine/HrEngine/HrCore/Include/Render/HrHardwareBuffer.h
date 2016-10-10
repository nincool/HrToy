#ifndef _HR_HARDWAREBUFFER_H_
#define _HR_HARDWAREBUFFER_H_

#include "HrCore/Include/Render/HrGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrHardwareBuffer : public HrGraphicsBuffer
	{
	public:
		HrHardwareBuffer();

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrGraphicsBuffer::EnumHardwareBufferBind bindFlag) override;
		
		virtual uint32 GetByteWidth() override;

	protected:
		uint32 m_nByteWidth;
		HrGraphicsBuffer::EnumHardwareBufferUsage m_usage;
		HrGraphicsBuffer::EnumHardwareBufferBind m_bindFlag;
	};
}


#endif




