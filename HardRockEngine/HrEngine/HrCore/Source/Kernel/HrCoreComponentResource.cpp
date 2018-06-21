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

HrTexturePtr HrCoreComponentResource::RetriveTexture(const std::string& strFile, HrTexture::EnumTextureType type)
{
	switch (type)
	{
	case HrTexture::TEX_TYPE_1D:
		break;
	case HrTexture::TEX_TYPE_2D:
		return HrCheckPointerCast<HrTexture>(m_pResourceManager->RetriveOrLoadResource(strFile, HrResource::RT_TEXTURE_2D));
	}

	return nullptr;
}

