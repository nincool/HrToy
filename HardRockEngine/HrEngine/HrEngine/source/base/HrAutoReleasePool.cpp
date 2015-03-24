#include "stdafx.h"
#include "HrAutoReleasePool.h"
#include "HrRef.h"

US_NS_HR;

CHrAutoReleasePool::CHrAutoReleasePool()
	:m_bIsClearing(false)
{
	m_vecManagedObject.reserve( 150 );
}

CHrAutoReleasePool::CHrAutoReleasePool(const std::string& name) 
	: m_strName(name), m_bIsClearing(false)
{
	m_vecManagedObject.reserve( 150 );
	CHrReleaseManager::Instance()->Push( this );
}

CHrAutoReleasePool::~CHrAutoReleasePool()
{
	HRLOG("Deallocing AutoreleasePool: %p AutoreleasePool: %s", this, m_strName );
	Clear();

	CHrReleaseManager::Instance()->Pop();
}

void CHrAutoReleasePool::AddObject( CHrRef* pRef )
{
	m_vecManagedObject.push_back( pRef );
}

void CHrAutoReleasePool::Clear()
{
	m_bIsClearing = true;

	for (const auto &obj : m_vecManagedObject)
	{
		obj->Release();
	}
	m_vecManagedObject.clear();

	m_bIsClearing = false;
}

bool CHrAutoReleasePool::Contains( CHrRef* pRef ) const
{
	for (const auto& obj : m_vecManagedObject)
	{
		if (obj == pRef)
		{
			return true;
		}
	}

	return false;
}

void CHrAutoReleasePool::Dump()
{

}

//------------------------------------------------------
//
//CHrReleaseManager
//
//------------------------------------------------------

CHrReleaseManager* CHrReleaseManager::m_s_instance;

CHrReleaseManager::CHrReleaseManager()
{
	m_vecReleaseStack.reserve( 10 );
}

CHrReleaseManager::~CHrReleaseManager()
{
	HRLOG( "Deallocing ReleaseManager: %p", this );
	while (!m_vecReleaseStack.empty())
	{
		CHrAutoReleasePool* pool = m_vecReleaseStack.back();

		//~CHrAutoReleasePool -> CHrReleaseManager->Pop()
		SAFE_DELETE( pool );
	}
}

void CHrReleaseManager::DestroyInstance()
{
	SAFE_DELETE( m_s_instance );
}

CHrAutoReleasePool* CHrReleaseManager::GetCurrentPool() const
{
	return m_vecReleaseStack.back();
}

bool CHrReleaseManager::IsObjectInPools( CHrRef* pRef ) const
{
	for (const auto& pool : m_vecReleaseStack)
	{
		if (pool->Contains( pRef ))
			return true;
	}

	return false;
}

void CHrReleaseManager::Push( CHrAutoReleasePool* pReleasePool )
{
	m_vecReleaseStack.push_back( pReleasePool );
}

void CHrReleaseManager::Pop()
{
	HRASSERT( !m_vecReleaseStack.empty(), "ReleaseManager Is Empty" );
	m_vecReleaseStack.pop_back();
}

CHrReleaseManager* CHrReleaseManager::Instance()
{
	if (m_s_instance == nullptr)
	{
		m_s_instance = new (std::nothrow) CHrReleaseManager();

		new CHrAutoReleasePool( "Hr Release Pool" );
	}

	return m_s_instance;
}

