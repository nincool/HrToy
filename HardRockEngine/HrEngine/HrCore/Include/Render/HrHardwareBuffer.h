#ifndef _HR_HARDWAREBUFFER_H_
#define _HR_HARDWAREBUFFER_H_

#include "HrCore/Include/Render/IGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrHardwareBuffer : public IGraphicsBuffer
	{
	public:
		HrHardwareBuffer();

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, IGraphicsBuffer::EnumHardwareBufferBind bindFlag) override;
		virtual uint32 GetByteWidth() override;
	protected:
		uint32 m_nByteWidth;
		IGraphicsBuffer::EnumHardwareBufferUsage m_usage;
		IGraphicsBuffer::EnumHardwareBufferBind m_bindFlag;
	};
}


#endif




