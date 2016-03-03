#include "Render/HrHardwareBuffer.h"

using namespace Hr;

HrHardwareBuffer::HrHardwareBuffer()
{
	m_nByteWidth = 0;
}

HrHardwareBuffer::HrHardwareBuffer(uint32 nByteWidth)
{
	m_nByteWidth = nByteWidth;
}
