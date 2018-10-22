#include "Kernel/HrResourceModule.h"
#include "Kernel/HrLog.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrMaterial.h"


using namespace Hr;

HrResourceModule::HrResourceModule()
{
	m_pResourceManager = HrMakeSharedPtr<HrResourceManager>();
	m_pResourceManager->InitResourceManager();
}

HrResourceModule::~HrResourceModule()
{
}

HrTexturePtr HrResourceModule::RetriveTexture(const std::string& strFile, HrTexture::EnumTextureType type)
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

HrMaterialPtr HrResourceModule::MakeMaterial(const std::string& strFile, const HrModelDataInfo::HrMaterialDataInfo& materialInfo)
{
	HrResourcePtr pMat = m_pResourceManager->RetriveResource(strFile, HrResource::RT_MATERIAL);
	if (!pMat)
	{
		HrMaterialPtr pNewMat = m_pResourceManager->MakeMaterial(materialInfo);
		return pNewMat;
	}
	else
	{
		BOOST_ASSERT(false);
		HRERROR("HrResourceModule::MakeMaterial Error!");
	}

	return HrCheckPointerCast<HrMaterial>(pMat);
}

