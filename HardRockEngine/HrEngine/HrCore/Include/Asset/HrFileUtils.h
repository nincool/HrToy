#ifndef _HR_FILEUTILS_H_
#define _HR_FILEUTILS_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrFileUtils
	{
	public:
		virtual ~HrFileUtils() {};

		virtual bool IsFileExist(const std::string& strFile) const;

		virtual bool IsAbsolutePath(const std::string& strPath) const;

		virtual std::string GetFullPathForFileName(const std::string& strFileName) const;

		virtual std::string GetWritablePath() const = 0;

		virtual std::string GetAppPath() const = 0;

		virtual std::shared_ptr<HrStreamData> GetFileData(const std::string& strFileName) = 0;
	protected:
		virtual bool IsFileExistInternal(const std::string& strFile) const = 0;
	};

}

#endif







