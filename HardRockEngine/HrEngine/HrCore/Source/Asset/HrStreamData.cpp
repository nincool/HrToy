#include "Asset/HrStreamData.h"

using namespace Hr;

HrStreamData::HrStreamData()
{
	m_readDataType = RDT_TXT;
}

HrStreamData::~HrStreamData()
{
}

void HrStreamData::SetReadDataType(EnumReadDataType readDataType)
{
	m_readDataType = readDataType;
}

char* HrStreamData::ResizeBuffer(uint64 nLength)
{
	m_vecStreamData.clear();
	m_vecStreamData.resize(nLength);
	
	return (char*)&m_vecStreamData[0];
}

char* HrStreamData::GetBufferPoint()
{
	return (char*)&m_vecStreamData[0];
}

uint64 HrStreamData::GetBufferSize()
{
	return m_vecStreamData.size();
}

void HrStreamData::ClearBuffer()
{
	m_vecStreamData.clear();
}

void HrStreamData::AddBuffer(char* pData, uint32 nSize)
{
	uint32 nOldSize = m_vecStreamData.size();
	m_vecStreamData.resize(nOldSize + nSize);
	memcpy((char*)&m_vecStreamData[nOldSize], pData, nSize);
}

