#ifndef _HR_HARDWAREBUFFER_H_
#define _HR_HARDWAREBUFFER_H_

#include "HrCore/Include/Render/IGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrHardwareBuffer : public IGraphicsBuffer
	{
	public:
		HrHardwareBuffer();

		virtual void BindVertexStream(char* pBuffer, uint32 nBufferSize, IGraphicsBuffer::EnumHardwareBufferUsage usage) override;

	protected:
		uint32 m_nByteWidth;
		IGraphicsBuffer::EnumHardwareBufferUsage m_usage;

	};
}


#endif




