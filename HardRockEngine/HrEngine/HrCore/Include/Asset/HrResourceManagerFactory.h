/************************************************************************ 
* 
*   DocName：HrResourceManagerFactory
* 
*   Brief： 资源管理器工厂负责创建资源管理器
* 
*   Author: Hr  
* 
*   Comment: 
* 
*   Date: [5/19/2016 By Hr]
*
************************************************************************/
#ifndef _HR_RESOURCEMANAGERFACTORY_H_
#define _HR_RESOURCEMANAGERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResourceManagerFactory
	{
		enum EnumResFactoryType
		{
			//SHADER 管理器
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
		T* GetResourceManager(EnumResFactoryType managerType)
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

		std::unordered_map<EnumResFactoryType, IResourceManager*> m_mapResManager;
	};
}

#endif

