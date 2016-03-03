#include "Asset/HrStreamData.h"

using namespace Hr;

HrStreamData::HrStreamData()
{
	m_readDataType = RDT_TXT;
}

HrStreamData::~HrStreamData()
{
}

void HrStreamData::SetReadDataType(_READ_DATA_TYPE_ readDataType)
{
	m_readDataType = readDataType;
}

void* HrStreamData::ResizeBuffer(uint64 nLength)
{
	m_vecStreamData.clear();
	m_vecStreamData.resize(nLength + 1);
	
	return &m_vecStreamData[0];
}


