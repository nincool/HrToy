#include "Asset/HrStreamData.h"

using namespace Hr;

HrStreamData::HrStreamData()
{
}

HrStreamData::HrStreamData(uint32 nStreamLength)
{
	ResizeBuffer(nStreamLength);
}

HrStreamData::~HrStreamData()
{
}

Byte* HrStreamData::ResizeBuffer(uint64 nLength)
{
	m_vecStreamData.clear();
	m_vecStreamData.resize(nLength);

	return static_cast<Byte*>(&m_vecStreamData[0]);
}

Byte* HrStreamData::GetBufferPoint()
{
	return static_cast<Byte*>(&m_vecStreamData[0]);
}

const Byte* HrStreamData::GetBufferPoint() const
{
	return static_cast<const Byte*>(&m_vecStreamData[0]);
}

uint64 HrStreamData::GetBufferSize()
{
	return m_vecStreamData.size();
}

uint64 HrStreamData::GetBufferSizeWithoutNULLTerminator()
{
	size_t nNull = 0;

	while (m_vecStreamData[m_vecStreamData.size() - 1 - nNull] == '\0')
	{
		++nNull;
	}
	return m_vecStreamData.size() - nNull;
}

void HrStreamData::ClearBuffer()
{
	m_vecStreamData.clear();
}

void HrStreamData::AddBuffer(uint8* pData, uint32 nSize)
{
	uint32 nOldSize = m_vecStreamData.size();
	m_vecStreamData.resize(nOldSize + nSize);
	memcpy((Byte*)&m_vecStreamData[nOldSize], pData, nSize);
}

HrStreamData& HrStreamData::operator=(HrStreamData& streamData)
{
	ResizeBuffer(streamData.m_vecStreamData.size());
	memcpy(&m_vecStreamData[0], &streamData.m_vecStreamData[0], streamData.m_vecStreamData.size());
	return *this;
}

void HrStreamData::CopyFrom(HrStreamData& streamData)
{
	this->operator=(streamData);
}

