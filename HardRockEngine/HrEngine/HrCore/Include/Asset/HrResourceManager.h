#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrCommon/include/HrSingleton.h"

#define HR_BUILDIN_RES_PATH "HR_BUILDIN_RESOURCE\\"

namespace Hr
{
	class HR_CORE_API HrResourceManager : public HrSingleTon<HrResourceManager>
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		void InitResourceManager();
		
		HrResource* LoadResource(const std::string& strFile, HrResource::EnumResourceType resType = HrResource::RT_UNKNOWN);

		HrResource* GetResource(const std::string& strFile, HrResource::EnumResourceType resType);
		HrResource* GetOrLoadResource(const std::string& strFile, HrResource::EnumResourceType resType);
		HrResource* GetOrAddResource(const std::string& strFile, HrResource::EnumResourceType resType);

		HrResource* GetSkyBoxResource(const std::string& strFile, HrResource::EnumResourceType resType);
		/*
			@brief	默认材质 [2/22/2017 By Hr]
		*/
		HrMaterial* GetDefaultMaterial();
		/*
			@brief	初始化时默认的效果 [11/15/2016 By Hr]
		*/
		HrRenderEffect* GetDefaultRenderEffect();


		void ReleaseAllResources();
	protected:
		/*
		@brief	只添加资源并不加载 [11/15/2016 By Hr]
		*/
		HrResource* AddModelResource(const std::string& strFile);
		HrResource* AddEffectResource(const std::string& strFile);
		HrResource* AddMeshResource(const std::string& strFile);
		HrResource* AddMaterialResource(const std::string& strFile);
		HrResource* AddTextureResource(const std::string& strFile);

		void CreateBuildInEffects();
		void CreateBuildInMaterial();

		HrResource* GetTexture(const std::string& strTextureName);
		HrResource* GetMesh(const std::string& strMeshName);
		HrResource* GetEffect(const std::string& strEffectName);
		HrResource* GetMaterial(const std::string& strMaterialName);
		HrResource* GetModel(const std::string& strModelName);

		void ReleaseResourceCache(std::unordered_map<size_t, HrResource*>& mapRes);
	protected:
		std::unordered_map<size_t, HrResource*> m_mapPrefabModels;
		std::unordered_map<size_t, HrResource*> m_mapMesh;
		std::unordered_map<size_t, HrResource*> m_mapMaterials;
		std::unordered_map<size_t, HrResource*> m_mapTextures;
		
		std::unordered_map<size_t, HrResource*> m_mapRenderEffects;
	};
}

#endif

