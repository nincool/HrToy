#ifndef _HR_RESOURCELOADER_H_
#define _HR_RESOURCELOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResourceLoader 
	{
	public:
		static bool LoadFromFile(std::string strFilePath, HrStreamData& data);
	};
}

#endif

