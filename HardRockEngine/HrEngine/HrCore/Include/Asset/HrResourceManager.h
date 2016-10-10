#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResourceManager 
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		virtual void InitResourceManager();
		virtual HrResource* LoadResource(std::string strName, std::string strFilePath);
		virtual HrResource* GetResource(std::string strName);

	protected:
		//std::unordered_map<std::string, IResource*> m_mapResource;
		std::unordered_map<size_t, HrResource*> m_mapResource;
	};
}

#endif

