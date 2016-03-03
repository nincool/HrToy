#ifndef _HR_RESOURCELOADER_H_
#define _HR_RESOURCELOADER_H_

#include "HrCore/Include/Asset/IResourceLoader.h"

namespace Hr
{
	class HrResourceLoader : public IResourceLoader
	{
	public:
		static void LoadFromFile(std::string strFilePath, HrStreamData& data);
	};
}

#endif




