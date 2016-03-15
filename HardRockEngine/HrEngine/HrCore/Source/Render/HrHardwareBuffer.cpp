#include "Render/HrHardwareBuffer.h"

using namespace Hr;

HrHardwareBuffer::HrHardwareBuffer()
{
	m_nByteWidth = 0;
	m_usage = IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE;
}

void HrHardwareBuffer::BindStream(char* pBuffer
	, uint32 nBufferSize
	, IGraphicsBuffer::EnumHardwareBufferUsage usage
	, IGraphicsBuffer::EnumHardwareBufferBind bindFlag)
{
	m_nByteWidth = nBufferSize;
	m_usage = usage;
	m_bindFlag = bindFlag;
}

uint32 HrHardwareBuffer::GetByteWidth()
{
	return m_nByteWidth;
}

