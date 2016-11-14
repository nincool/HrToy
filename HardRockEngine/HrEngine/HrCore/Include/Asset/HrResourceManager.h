#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrResource.h"

#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HR_CORE_API HrResourceManager : public HrSingleTon<HrResourceManager>
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		void InitResourceManager();
		
		HrResource* LoadResource(const std::string& strFile);

		HrResource* GetResource(const std::string& strFile, HrResource::EnumResourceType resType);

		HrResource* CreateMeshManual(const std::string& strName, std::string& strFile);
	protected:
		HrResource* AddFBXResource(const std::string& strFile);
		HrResource* AddEffectResource(const std::string& strFile);

		void CreateBuildInEffects();

		HrResource* GetEffect(const std::string& strEffectName);
	protected:
		std::unordered_map<size_t, HrResource*> m_mapPrefebModels;
		std::unordered_map<size_t, HrResource*> m_mapMesh;
		
		std::unordered_map<size_t, HrResource*> m_mapRenderEffects;
	};
}

#endif

