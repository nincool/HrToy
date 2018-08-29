#ifndef _HR_JSONLOADER_H_
#define _HR_JSONLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

namespace Hr
{
	class HrJsonLoader
	{
	public:
		HrJsonLoader();
		~HrJsonLoader();

		void Load(std::string& strFile, HrModelDataInfo& modelDesc);

	private:

	};
}


#endif



