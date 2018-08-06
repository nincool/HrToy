#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HR_CORE_API HrResourceManager
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		void InitResourceManager();
		
		HrResourcePtr RetriveResource(const std::string& strFile, HrResource::EnumResourceType resType);
		HrResourcePtr RetriveOrLoadResource(const std::string& strFile, HrResource::EnumResourceType resType);
		HrResourcePtr RetriveOrAddResource(const std::string& strFile, HrResource::EnumResourceType resType);

		HrResourcePtr GetDefaultMaterial();
		HrTexture* GetDefaultTexture();
		HrResourcePtr GetDefaultRenderEffect();


		void ReleaseAllResources();
	protected:
		/**
		 @Comment: 加载资源 [1/30/2018 By Hr]
		*/
		HrResourcePtr LoadResource(const std::string& strFile, HrResource::EnumResourceType resType = HrResource::RT_UNKNOWN);
		/*
		@brief	只添加资源并不加载 [11/15/2016 By Hr]
		*/
		HrResourcePtr AddResource(const std::string& strFile, HrResource::EnumResourceType resType);

		HrResourcePtr AddModelResource(const std::string& strFile);
		HrResourcePtr AddMeshModelResource(const std::string& strFile);
		HrResourcePtr AddEffectResource(const std::string& strFile);
		HrResourcePtr AddMeshResource(const std::string& strFile);
		HrResourcePtr AddMaterialResource(const std::string& strFile);

		HrResourcePtr AddTesture2DResource(const std::string& strFile);

		void CreateBuildInTexture();
		void CreateBuildInEffects();
		void CreateBuildInMaterial();

		HrResourcePtr GetTexture2D(const std::string& strTextureName);
		HrResourcePtr GetMesh(const std::string& strMeshName);
		HrResourcePtr GetEffect(const std::string& strEffectName);
		HrResourcePtr GetModel(const std::string& strModelName);
		HrResourcePtr GetMeshModel(const std::string& strModelName);

		const HrResourcePtr& GetMaterial(const std::string& strMaterialName);

		void ReleaseResourceCache(std::unordered_map<size_t, HrResourcePtr>& mapRes);
	protected:
		std::unordered_map<size_t, HrResourcePtr> m_mapPrefabModels; //depre
		std::unordered_map<size_t, HrResourcePtr> m_mapMeshModels;
		std::unordered_map<size_t, HrResourcePtr> m_mapMesh;
		std::unordered_map<size_t, HrResourcePtr> m_mapMaterials;
		std::unordered_map<size_t, HrResourcePtr> m_mapTextures2D;
		
		std::unordered_map<size_t, HrResourcePtr> m_mapRenderEffects;

		HrTexture* m_pDefaultTexture;
		HrRenderEffectPtr m_pDefaultRenderEffect;
		HrMaterialPtr m_pDefaultMaterial;
	};

}

#endif

