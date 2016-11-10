#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrModelLoader
	{
	public:
		HrModelLoader();
		virtual ~HrModelLoader();

	public:
		virtual void Load(std::string& strFile) = 0;
		

	};
}


#endif



