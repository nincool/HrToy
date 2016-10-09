#ifndef _I_RESOURCEMANAGER_H_
#define _I_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class IResourceManager
	{
	public:
		virtual ~IResourceManager(){}

		virtual void InitResourceManager() = 0;
		virtual IResource* LoadResource(std::string strName, std::string strFilePath) = 0;
		virtual IResource* GetResource(std::string strName) = 0;
	};
}


#endif