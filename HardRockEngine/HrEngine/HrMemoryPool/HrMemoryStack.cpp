#include "stdafx.h"
#include "HrMemoryStack.h"
#include "HrLowDebug.h"
#include "HrMemoryStackToken.h"

using namespace HrPool;
CHrMemoryStack::CHrMemoryStack( CHrLowDebug* pDebugLog )
{
	m_pDebugLog = pDebugLog;
	m_pStackTokenHead = new CHrMemoryStackToken( HR_MEM_BLOCK_MIN,  m_pDebugLog);

	m_nMaxMemoryAddress = 0;
	m_nAllBlockCount = 0;
	m_nMemoryUsed = 0;
	m_bCloseFlag = false;

}

CHrMemoryStack::~CHrMemoryStack()
{
	m_pDebugLog->Debug2File( "Memory Stack: Max Point = 0x%p\n", m_nMaxMemoryAddress );

	SAFE_DELETE( m_pStackTokenHead );
}

void* CHrMemoryStack::Mallock( size_t nSize )
{
	void* pRetMemory = nullptr;
	if (0 >= nSize)
	{
		m_pDebugLog->Debug2File( "CHrMemoryStack::Mallock Error! Mallock MemorySize[%d]", nSize );

		return pRetMemory;
	}
	
	if (m_pStackTokenHead != nullptr)
	{
		pRetMemory = m_pStackTokenHead->Malloc( nSize, m_nAllBlockCount, m_nMemoryUsed );
		if (m_nMaxMemoryAddress < reinterpret_cast<uint64>(pRetMemory))
		{
			m_nMaxMemoryAddress = reinterpret_cast<uint64>(pRetMemory);
		}

		return pRetMemory;
	}

	return pRetMemory;
}

bool CHrMemoryStack::Free( void* pMemory )
{
	bool bRetVal = m_pStackTokenHead->Free( pMemory, m_bCloseFlag );

	return bRetVal;
}

void CHrMemoryStack::PrintStack()
{
	m_pStackTokenHead->PrintStack();
}

void CHrMemoryStack::PrintInfo()
{
	m_pDebugLog->Debug2File( "block=%d, use=%d kbytes, biggest=%p\n"
		, m_nAllBlockCount
		, m_nMemoryUsed / 1024
		, m_nMaxMemoryAddress );
}
