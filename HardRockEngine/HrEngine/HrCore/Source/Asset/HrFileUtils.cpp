#include "Asset/HrFileUtils.h"

using namespace Hr;

bool HrFileUtils::IsFileExist(const std::string& strFile) const
{
	return true;

	if (IsAbsolutePath(strFile))
	{
		return IsFileExistInternal(strFile);
	}
	else
	{
		std::string strFullPath = GetFullPathForFileName(strFile);
	}
}

bool HrFileUtils::IsAbsolutePath(const std::string& strPath) const
{
	return (strPath[0] == '/');
}

std::string HrFileUtils::GetFullPathForFileName(const std::string& strFileName) const
{
	if (strFileName.empty())
	{
		return "";
	}

	if (IsAbsolutePath(strFileName))
	{
		return strFileName;
	}

	return "";
}

