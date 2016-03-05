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

