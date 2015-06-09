#include "stdafx.h"
#include "HrPoolManager.h"
#include "HrMemoryBase.h"
#include "HrLowDebug.h"
#include "HrMemoryStack.h"
#include "HrMemoryRegister.h"

using namespace HrPool;

CHrPoolManager::CHrPoolManager(bool bOpenRegister) : m_pDebugLog(new CHrLowDebug(".", "MemDetect", true))
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
	//先通知私用者清除内存，以防止全局单利对象的存在
	for (auto item : m_lisPoolListener)
	{
		item->OnNotice(CHrPoolListener::NOTICE_RELEASE);
	}

	SAFE_DELETE( m_pMemoryStack );
	SAFE_DELETE( m_pRegister );

	m_pDebugLog->Debug2File( "Hr Memory Pool close.\n" );

	SAFE_DELETE( m_pDebugLog );
}

void* CHrPoolManager::Malloc( size_t nSize, char* szInfo /*= NULL */ )
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
	m_pMemoryStack->Free( pMemory );

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

void CHrPoolManager::PrintTree()
{
	m_pMemoryStack->PrintStack();
}

void CHrPoolManager::PrintInfo()
{
	if (m_pRegister != nullptr)
	{
		m_pRegister->PrintInfo();
	}

	m_pMemoryStack->PrintInfo();
}

void CHrPoolManager::Release()
{

}
