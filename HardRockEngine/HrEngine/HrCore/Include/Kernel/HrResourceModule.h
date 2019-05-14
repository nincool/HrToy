#ifndef _HR_CORECOMPONENTEVENT_H_
#define _HR_CORECOMPONENTEVENT_H_

#include "HrCore/Include/Kernel/HrModule.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrTexture.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"

#include "HrCore/Include/Asset/HrMaterial.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrMeshModel.h"
#include "HrCore/Include/Asset/HrSceneItems.h"

namespace Hr
{
	class HR_CORE_API HrResourceModule : public HrModule
	{
	public:
		HrResourceModule();
		~HrResourceModule();

		virtual bool InitComponent() override;

		template <typename T>
		std::shared_ptr<T> RetriveResource(const std::string& strFile = "", bool bAdd = true, bool bLoad = true);
		
		template <typename T>
		bool RemoveResource(const std::string& strFile);

		HrTexturePtr RetriveTexture(const std::string& strFile, HrTexture::EnumTextureType type);
		HrMaterialPtr MakeMaterial(const std::string& strFile, const HrModelDataInfo::HrMaterialDataInfo& materialInfo);
	private:
		HrResource::EnumResourceType GetResourceType(const std::string& strName);
	private:
		HrResourceManagerPtr m_pResourceManager;
	};

	template <typename T>
	std::shared_ptr<T> HrResourceModule::RetriveResource(const std::string& strFile, bool bAdd /*= false*/, bool bLoad /*= false*/)
	{
		HrResource::EnumResourceType resType = GetResourceType(typeid(T).name());
		if (resType == HrResource::RT_EFFECT && strFile.empty())
			return HrCheckPointerCast<T>(m_pResourceManager->GetDefaultRenderEffect());

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

	template <typename T>
	bool HrResourceModule::RemoveResource(const std::string& strFile)
	{
		HrResource::EnumResourceType resType = HrResource::RT_UNKNOWN;
		auto pTypeName = typeid(T).name();
		if (pTypeName == typeid(HrMaterial).name())
		{
			resType = HrResource::RT_MATERIAL;
		}
		else if (pTypeName == typeid(HrRenderEffect).name())
		{
			resType = HrResource::RT_EFFECT;
		}
		else if (pTypeName == typeid(HrMesh).name())
		{
			resType = HrResource::RT_MESH;
		}
		else if (pTypeName == typeid(HrMeshModel).name())
		{
			resType = HrResource::RT_MESHMODEL;
		}


		return m_pResourceManager->RemoveResource(strFile, resType);
	}

}


#endif
