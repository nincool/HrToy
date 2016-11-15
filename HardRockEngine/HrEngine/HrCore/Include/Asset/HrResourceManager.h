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
		HrResource* GetOrLoadResource(const std::string& strFile, HrResource::EnumResourceType resType);

		/*
			@brief	初始化时默认的效果 [11/15/2016 By Hr]
		*/
		HrRenderEffect* GetDefaultRenderEffect();
		/*
			@brief	只添加资源并不加载 [11/15/2016 By Hr]
		*/
		HrResource* AddFBXResource(const std::string& strFile);
		HrResource* AddEffectResource(const std::string& strFile);
		HrResource* AddMeshResource(const std::string& strFile);
	protected:

		void CreateBuildInEffects();

		HrResource* GetMesh(const std::string& strMeshName);
		HrResource* GetEffect(const std::string& strEffectName);
	protected:
		std::unordered_map<size_t, HrResource*> m_mapPrefebModels;
		std::unordered_map<size_t, HrResource*> m_mapMesh;
		
		std::unordered_map<size_t, HrResource*> m_mapRenderEffects;
	};
}

#endif

