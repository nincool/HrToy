#include "HrRef.h"
#include "HrAutoReleasePool.h"

US_NS_HR;

CHrRef::CHrRef()
	: m_nReferenceCount(1)
{
}

CHrRef::~CHrRef()
{

}

void CHrRef::Retain()
{
	HRASSERT(m_nReferenceCount > 0, "reference count should be greater than 0");
	++m_nReferenceCount;
}

void CHrRef::Release()
{
	HRASSERT( m_nReferenceCount > 0, "reference count should be greater than 0" );
	--m_nReferenceCount;

	if (m_nReferenceCount == 0)
	{
		CHrReleaseManager* pReleaseManager = CHrReleaseManager::Instance();
		if (pReleaseManager->GetCurrentPool()->IsClearing() && pReleaseManager->IsObjectInPools( this ))
		{
			HRASSERT( false, "The reference shouldn't be 0 because it is still in autorelease pool." );
		}

		delete this;
	}
}

CHrRef* CHrRef::AutoRelease()
{
	CHrReleaseManager::Instance()->GetCurrentPool()->AddObject( this );
	return this;
}

uint CHrRef::GetReferenceCount() const
{
	return m_nReferenceCount;
}




