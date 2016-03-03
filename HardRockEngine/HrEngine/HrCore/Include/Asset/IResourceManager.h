#ifndef _I_RESOURCEMANAGER_H_
#define _I_RESOURCEMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IResourceManager : public ResourceAllocatedObject
	{
	public:
		virtual ~IResourceManager(){}

		virtual void InitResourceManager() = 0;
		virtual IResource* LoadResource(std::string strName, std::string strFilePath) = 0;

		virtual IShaderCompiler*  GetShareShaderCompiler() = 0;
	};
}


#endif