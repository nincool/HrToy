#include "Asset/HrStreamData.h"

#define VECTOR_ALLOC

using namespace Hr;

HrStreamData::HrStreamData()
{
	m_readDataType = RDT_TXT;
	m_pStreamData = nullptr;
	m_nStreamLength = 0;
}

HrStreamData::~HrStreamData()
{
	SAFE_DELETE(m_pStreamData);
}

void HrStreamData::SetReadDataType(EnumReadDataType readDataType)
{
	m_readDataType = readDataType;
}

char* HrStreamData::ResizeBuffer(uint64 nLength)
{
#ifdef VECTOR_ALLOC
	m_vecStreamData.clear();
	m_vecStreamData.resize(nLength);

	return (char*)&m_vecStreamData[0];
#else
	if (m_nStreamLength >= nLength)
	{
		return m_pStreamData;
	}
	else
	{
		SAFE_DELETE(m_pStreamData);
		m_pStreamData = new char[nLength];
		memset(m_pStreamData, 0, nLength);
		m_nStreamLength = nLength;
	}


	return m_pStreamData;
#endif // VECTOR_ALLOC
}

char* HrStreamData::GetBufferPoint()
{
#ifdef VECTOR_ALLOC
	return (char*)&m_vecStreamData[0];
#else
	return m_pStreamData;
#endif // VECTOR_ALLOC
}

uint64 HrStreamData::GetBufferSize()
{
#ifdef VECTOR_ALLOC
	return m_vecStreamData.size();
#else
	return m_nStreamLength;
#endif // VECTOR_ALLOC
}

uint64 HrStreamData::GetBufferSizeWithoutNULLTerminator()
{
#ifdef VECTOR_ALLOC
	size_t nNull = 0;

	while (m_vecStreamData[m_vecStreamData.size() - 1 - nNull] == '\0')
	{
		++nNull;
	}
	return m_vecStreamData.size() - nNull;
#else
	return m_nStreamLength;
#endif // VECTOR_ALLOC	
}

void HrStreamData::ClearBuffer()
{
#ifdef VECTOR_ALLOC
	m_vecStreamData.clear();
#else
	memset(m_pStreamData, 0, m_nStreamLength);
	m_nStreamLength = 0;
#endif // VECTOR_ALLOC
}

void HrStreamData::AddBuffer(char* pData, uint32 nSize)
{
#ifdef VECTOR_ALLOC
	uint32 nOldSize = m_vecStreamData.size();
	m_vecStreamData.resize(nOldSize + nSize);
	memcpy((char*)&m_vecStreamData[nOldSize], pData, nSize);
#else
	char* pNewStream = new char[m_nStreamLength + nSize];
	memset(pNewStream, 0, nSize);
	if (m_pStreamData != nullptr)
	{
		memcpy(pNewStream, m_pStreamData, m_nStreamLength);
	}
	memcpy(pNewStream + m_nStreamLength, pData, nSize);
	SAFE_DELETE(m_pStreamData);
	m_pStreamData = pNewStream;

	m_nStreamLength += nSize;
#endif // VECTOR_ALLOC
}

