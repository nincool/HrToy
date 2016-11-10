#ifndef _HR_RESOURCEMANAGER_H_
#define _HR_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HrResourceManager : public HrSingleTon<HrResourceManager>
	{
	public:
		HrResourceManager();
		~HrResourceManager();

		void InitResourceManager();
		
		HrResource* LoadResource(std::string& strFile);
		
		HrResource* GetResource(std::string& strName);

	protected:
		HrResource* AddFBXResource(std::string& strFile);
	protected:
		std::unordered_map<size_t, HrResource*> m_mapPrefebModels;
	};
}

#endif

