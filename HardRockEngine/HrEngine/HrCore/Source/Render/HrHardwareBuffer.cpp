#include "Render/HrHardwareBuffer.h"

using namespace Hr;

HrHardwareBuffer::HrHardwareBuffer()
{
	m_nByteWidth = 0;
	m_usage = HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE;
}

void HrHardwareBuffer::BindStream(char* pBuffer
	, uint32 nBufferSize
	, HrGraphicsBuffer::EnumHardwareBufferUsage usage
	, HrGraphicsBuffer::EnumHardwareBufferBind bindFlag)
{
	m_nByteWidth = nBufferSize;
	m_usage = usage;
	m_bindFlag = bindFlag;
}

uint32 HrHardwareBuffer::GetByteWidth()
{
	return m_nByteWidth;
}

