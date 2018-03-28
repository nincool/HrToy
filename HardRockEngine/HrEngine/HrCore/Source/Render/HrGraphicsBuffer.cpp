#include "HrCore/Include/Render/HrGraphicsBuffer.h"

using namespace Hr;


HrGraphicsBuffer::HrGraphicsBuffer()
{
	m_nByteWidth = 0;
	m_usage = HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE;
}

HrGraphicsBuffer::~HrGraphicsBuffer()
{

}

void HrGraphicsBuffer::BindStream(const char* pBuffer
	, uint64 nBufferSize
	, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
	, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag)
{
	m_nByteWidth = nBufferSize;
	m_usage = usage;
	m_bindFlag = bindFlag;

}

uint32 HrGraphicsBuffer::GetByteWidth()
{
	return m_nByteWidth;
}

HrGraphicsBuffer::EnumGraphicsBufferUsage Hr::HrGraphicsBuffer::GetUsage()
{
	return m_usage;
}

