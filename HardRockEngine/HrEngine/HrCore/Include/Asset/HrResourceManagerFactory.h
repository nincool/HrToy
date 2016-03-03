#ifndef _HR_RESOURCEMANAGERFACTORY_H_
#define _HR_RESOURCEMANAGERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrResourceManagerFactory : public RenderSysAllocatedObject
	{
		enum _RES_FACTORY_TYPE_
		{
			RFT_EFFECTMANAGER,
		};

	public:
		HrResourceManagerFactory();
		~HrResourceManagerFactory();

		static HrResourceManagerFactory& GetInstance();
		static void ReleaseInstance();

		void CreateResourceManager();

		HrRenderEffectManager* GetEffectManager();

		template <typename T>
		T* GetResourceManager(_RES_FACTORY_TYPE_ managerType)
		{
			auto item = m_mapResManager.find(managerType);
			if (item != m_mapResManager.end())
			{
				return static_cast<T*>(item->second);
			}
			return nullptr;
		}

		void Release();
	private:
		static HrResourceManagerFactoryPtr m_s_pUniqueResManagerFactory;

		std::unordered_map<_RES_FACTORY_TYPE_, IResourceManager*> m_mapResManager;
	};
}

#endif