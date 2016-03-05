#include "Render/HrHardwareBuffer.h"

using namespace Hr;

HrHardwareBuffer::HrHardwareBuffer()
{
	m_nByteWidth = 0;
	m_usage = IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE;
}

void HrHardwareBuffer::BindVertexStream(char* pBuffer, uint32 nBufferSize, IGraphicsBuffer::EnumHardwareBufferUsage usage)
{
	m_nByteWidth = nBufferSize;
	m_usage = usage;
}

