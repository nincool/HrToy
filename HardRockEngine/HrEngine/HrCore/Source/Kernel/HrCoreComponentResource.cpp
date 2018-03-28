#include "Kernel/HrCoreComponentResource.h"
#include "Asset/HrResourceManager.h"

using namespace Hr;

HrCoreComponentResource::HrCoreComponentResource()
{
	m_pResourceManager = HrMakeSharedPtr<HrResourceManager>();
	m_pResourceManager->InitResourceManager();
}

HrCoreComponentResource::~HrCoreComponentResource()
{
}

