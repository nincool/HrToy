#ifndef _HR_FILEUTILS_H_
#define _HR_FILEUTILS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"
#include <experimental/filesystem>

namespace Hr
{
	class HR_CORE_API HrFileUtils : public HrSingleTon<HrFileUtils>
	{
	public:
		HrFileUtils();
		~HrFileUtils() {};

		bool IsFileExist(const std::string& strFile) const;

		bool IsAbsolutePath(const std::string& strPath) const;

		std::string GetFullPathForFileName(const std::string& strFileName) const;

		std::string GetFileSuffix(const std::string& strFile) const;

		std::string GetWritablePath() const;
		std::string GetMediaPath() const;

		std::string GetAppPath() const;

		std::string ReplaceFileName(const std::string& strFile, const std::string& strName) const;

		std::string GetFileNameWithSuffix(const std::string& strFile) const;
		std::string GetFilePath(const std::string& strFile) const;
		std::string GetFileName(const std::string& strFile) const;

		HrStreamDataPtr GetFileData(const std::string& strFile);

		bool WriteDataToFile(const std::string& strFile, const std::string& strData);
		bool WriteDataToFile(const std::string& strFile, const HrStreamDataPtr& pStreamData);

		void AddSearchDirectory(const std::string& strPath);

	public:
		static std::string m_s_strSeparator;
	private:
		std::string m_strAppPath;
		std::string m_strMediaPath;
		std::vector<std::experimental::filesystem::path> m_vecSearchDirectorys;
		

	};

}

#endif







