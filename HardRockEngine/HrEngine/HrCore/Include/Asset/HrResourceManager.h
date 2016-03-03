#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/Asset/IResourceManager.h"

namespace Hr
{
	class HrResourceManager : public IResourceManager
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		virtual void InitResourceManager() override;
		virtual IResource* LoadResource(std::string strName, std::string strFilePath) override;
	protected:
		std::unordered_map<std::string, IResource*> m_mapResource;
	};
}

#endif

