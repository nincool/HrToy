#ifndef _HR_CORECOMPONENTEVENT_H_
#define _HR_CORECOMPONENTEVENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrTexture.h"

namespace Hr
{
	class HR_CORE_API HrCoreComponentResource : public HrCoreComponent
	{
	public:
		HrCoreComponentResource();
		~HrCoreComponentResource();

		template <typename T>
		std::shared_ptr<T> RetriveResource(const std::string& strFile = "", bool bAdd = true, bool bLoad = true);

		HrTexturePtr RetriveTexture(const std::string& strFile, HrTexture::EnumTextureType type);

	private:
		HrResourceManagerPtr m_pResourceManager;
	};

	template <typename T>
	std::shared_ptr<T> HrCoreComponentResource::RetriveResource(const std::string& strFile, bool bAdd /*= false*/, bool bLoad /*= false*/)
	{
		HrResource::EnumResourceType resType = HrResource::RT_UNKNOWN;
		auto pTypeName = typeid(T).name();
		if (pTypeName == typeid(HrModel).name())
		{
			resType = HrResource::RT_MODEL;
		}
		else if (pTypeName == typeid(HrMaterial).name())
		{
			resType = HrResource::RT_MATERIAL;
			if (strFile.empty())
				return HrCheckPointerCast<T>(m_pResourceManager->GetDefaultMaterial());
		}
		else if (pTypeName == typeid(HrRenderEffect).name())
		{
			resType = HrResource::RT_EFFECT;
			if (strFile.empty())
				return HrCheckPointerCast<T>(m_pResourceManager->GetDefaultRenderEffect());
		}
		else if (pTypeName == typeid(HrMesh).name())
		{
			resType = HrResource::RT_MESH;
		}
		else if (pTypeName == typeid(HrMeshModel).name())
		{
			resType = HrResource::RT_MESHMODEL;
		}


		if (!bAdd && !bLoad)
		{
			return HrCheckPointerCast<T>(m_pResourceManager->RetriveResource(strFile, resType));
		}
		else if (bAdd && !bLoad)
		{
			return HrCheckPointerCast<T>(m_pResourceManager->RetriveOrAddResource(strFile, resType));
		}
		else if (bAdd && bLoad)
		{
			return HrCheckPointerCast<T>(m_pResourceManager->RetriveOrLoadResource(strFile, resType));
		}

		return nullptr;
	}

}


#endif
