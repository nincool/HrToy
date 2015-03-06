#include "stdafx.h"
#include "HrPoolManager.h"
#include "HrMemoryBase.h"
#include "HrLowDebug.h"
#include "HrMemoryStack.h"
#include "HrMemoryRegister.h"

using namespace HrPool;

CHrPoolManager::CHrPoolManager(bool bOpenRegister) : m_pDebugLog(new CHrLowDebug("..", "Test", false))
{
	m_pMemoryStack = new CHrMemoryStack( m_pDebugLog );
	m_pRegister = nullptr;
	if (bOpenRegister)
	{
		m_pRegister = new CHrMemoryRegister( m_pDebugLog );
	}
	m_pDebugLog->Debug2File( "Hr Memory Pool Open Register Flag=%d\n", bOpenRegister );
}

CHrPoolManager::~CHrPoolManager()
{
	SAFE_DELETE( m_pMemoryStack );
	SAFE_DELETE( m_pRegister );

	//×îºóÐ¶ÔØ
	SAFE_DELETE( m_pDebugLog );
}

void* CHrPoolManager::Malloc( int nSize, char* szInfo /*= NULL */ )
{
	void* pRetMemory = nullptr;
	pRetMemory = m_pMemoryStack->Mallock( nSize );
	if (pRetMemory != nullptr)
	{
		RegisterMemoryInfo( pRetMemory, szInfo );
	}

	return pRetMemory;
}

void CHrPoolManager::Free( void* pMemory )
{
	if (pMemory != nullptr)
	{
		UnRegisterMemoryInfo( pMemory );
	}
}

void CHrPoolManager::RegisterMemoryInfo( void* pMemory, char* szInfo )
{
	if (pMemory != nullptr && m_pRegister != nullptr)
	{
		m_pRegister->Add( pMemory, szInfo );
	}
}

void CHrPoolManager::UnRegisterMemoryInfo( void* pMemory )
{
	if (pMemory != nullptr && m_pRegister != nullptr)
	{
		m_pRegister->Del( pMemory );
	}
}
