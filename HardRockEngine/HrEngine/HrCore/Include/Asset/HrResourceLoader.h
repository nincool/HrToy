#ifndef _HR_RESOURCELOADER_H_
#define _HR_RESOURCELOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"


namespace Hr
{
	class HrResourceLoader : public HrSingleTon<HrResourceLoader>
	{
	public:
		HrResourceLoader();
		~HrResourceLoader();

		void SyncLoad(HrResource* pRes);

	private:


	};
}

#endif

