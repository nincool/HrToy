#include "stdafx.h"
#include "HrMemoryRegister.h"
#include "HrLowDebug.h"

using namespace HrPool;

CHrMemoryRegister::CHrMemoryRegister( CHrLowDebug* pDebugLog )
{
	m_pDebugLog = pDebugLog;
}

CHrMemoryRegister::~CHrMemoryRegister()
{
}

void CHrMemoryRegister::Add( void* pMemory, char* szInfo )
{
	if (pMemory > m_pMaxMemoryAddress)
	{
		m_pMaxMemoryAddress = pMemory;
	}

	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (m_registerArr[i].m_pMemory == nullptr)
		{
			++m_nMemoryAddressCount;
			RegisterCopy( &(m_registerArr[i]), pMemory, szInfo );

			return;
		}
	}

	if (HR_MEMORY_REGISTER_MAX <= m_nUsedMax)
	{
		m_pDebugLog->Debug2File( "*******ERROR******** CMemoryRegister if full!\n" );
		return;
	}

	RegisterCopy( &(m_registerArr[m_nUsedMax]), pMemory, szInfo );
	++m_nMemoryAddressCount;
	++m_nUsedMax;
}

void CHrMemoryRegister::RegisterCopy( SHrMemoryRegister* pDest, void* pMemory, char* szInfo )
{
	pDest->m_pMemory = pMemory;
	if (szInfo != nullptr)
	{
		ZeroMemory( pDest->m_szInfo, HR_MEMORY_BLOCK_INFO_MAX_SIZE );
		memcpy( pDest->m_szInfo, szInfo, HR_MEMORY_BLOCK_INFO_MAX_SIZE-1 );
	}
	else
	{
		HR_CLEAN_CHAR_BUFFER( pDest->m_szInfo );
	}
}

void CHrMemoryRegister::Del( void* pMemory )
{
	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (pMemory == m_registerArr[i].m_pMemory)
		{
			--m_nMemoryAddressCount;
			m_registerArr[i].m_pMemory = nullptr;
			HR_CLEAN_CHAR_BUFFER( m_registerArr[i].m_szInfo );

			return;
		}
	}
}

void CHrMemoryRegister::Modify( void* pOld, void* pNew )
{
	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (pOld == m_registerArr[i].m_pMemory)
		{
			m_registerArr[i].m_pMemory = pNew;

			if (pNew > m_pMaxMemoryAddress)
			{
				m_pMaxMemoryAddress = pNew;
			}

			return;
		}
	}

	m_pDebugLog->Debug2File( "****ERROR**** CMemroyRegister::Modeify():I can't found point!\n" );

	return;
}

void CHrMemoryRegister::PrintInfo()
{
	m_pDebugLog->Debug2File( "memory pool: %d / %d, the biggest = %p\n", m_nMemoryAddressCount, m_nUsedMax + 1, m_pMaxMemoryAddress );
}




