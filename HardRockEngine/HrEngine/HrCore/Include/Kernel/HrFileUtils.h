#ifndef _HR_FILEUTILS_H_
#define _HR_FILEUTILS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"
#include <experimental/filesystem>

namespace Hr
{
	class HrFileUtils : public HrSingleTon<HrFileUtils>
	{
	public:
		HrFileUtils();
		~HrFileUtils() {};

		bool IsFileExist(const std::string& strFile) const;

		bool IsAbsolutePath(const std::string& strPath) const;

		std::string GetFullPathForFileName(const std::string& strFileName) const;

		std::string GetFileSuffix(const std::string& strFile) const;

		std::string GetWritablePath() const;

		std::string GetAppPath() const;

		std::string ReplaceFileName(const std::string& strFile, const std::string& strName) const;

		HrStreamDataPtr GetFileData(const std::string& strFile);

		void AddSearchPath(const std::string& strPath);
	private:
		std::string m_strAppPath;
		std::vector<std::experimental::filesystem::path> m_vecSearchPaths;
		

	};

}

#endif







