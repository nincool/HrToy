#ifndef _HR_FBXLOADER_H_
#define _HR_FBXLOADER_H_

#include "HrCore/Include/Asset/Loader/HrModelLoader.h"

namespace Hr
{
	class HrFBXLoader : public HrModelLoader
	{
	public:
		HrFBXLoader();
		~HrFBXLoader();

		virtual void Load(std::string& strFile) override;

	};
}


#endif



