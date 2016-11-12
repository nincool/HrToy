#include "Kernel/HrFileUtils.h"
#include "Asset/HrStreamData.h"
#include <fstream>

using namespace Hr;
using namespace std::experimental;


HrFileUtils::HrFileUtils()
{
	char cBuf[MAX_PATH];
	::GetModuleFileNameA(nullptr, cBuf, sizeof(cBuf));
	m_strAppPath = cBuf;
	m_strAppPath = m_strAppPath.substr(0, m_strAppPath.rfind("\\") + 1);
	AddSearchPath(m_strAppPath);
	std::string strAssetPath = m_strAppPath.substr(0, m_strAppPath.rfind("\\") + 1);
	AddSearchPath(strAssetPath);
	strAssetPath = strAssetPath + "\\Media\\";
	AddSearchPath(strAssetPath);
}

bool HrFileUtils::IsFileExist(const std::string& strFile) const
{
	std::string strFileFullPath = strFile;
	if (!IsAbsolutePath(strFile))
	{
		strFileFullPath = GetFullPathForFileName(strFile);
	}

	return filesystem::exists(strFileFullPath);
}

bool HrFileUtils::IsAbsolutePath(const std::string& strPath) const
{
	filesystem::path filePath(strPath);

	return filePath.is_absolute();
}

std::string HrFileUtils::GetFullPathForFileName(const std::string& strFileName) const
{
	if (strFileName.empty())
	{
		return "";
	}

	filesystem::path filePath(strFileName);
	if (!filePath.is_absolute())
	{
		filesystem::path fileFullPath = filesystem::path(m_strAppPath) / filePath;
		for (auto item : m_vecSearchPaths)
		{
			fileFullPath = item / filePath;
			if (filesystem::exists(fileFullPath))
			{
				return fileFullPath.string();
			}
		}
	}
	else if (filesystem::exists(strFileName))
	{
		return filePath.string();
	}

	return "";
}

std::string HrFileUtils::GetWritablePath() const
{
	return "";
}

std::string HrFileUtils::GetAppPath() const
{
	return m_strAppPath;
}

HrStreamDataPtr HrFileUtils::GetFileData(const std::string& strFileName)
{
	HrStreamDataPtr pFileStream = std::make_shared<HrStreamData>();

	std::string strFullPath = GetFullPathForFileName(strFileName);
	if (strFullPath.empty())
	{
		return pFileStream;
	}

	std::fstream fileStream(strFileName.c_str(), std::ios::in);
	fileStream.seekg(0, std::ios::end);
	std::uint64_t nFileLength = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);

	size_t nLength = static_cast<size_t>(nFileLength);
	pFileStream->ResizeBuffer(nLength);
	fileStream.read(pFileStream->GetBufferPoint(), nLength);
	fileStream.close();

	return pFileStream;
}

void HrFileUtils::AddSearchPath(std::string& strPath)
{
	m_vecSearchPaths.emplace_back(filesystem::path(strPath));
}

std::string HrFileUtils::GetFileSuffix(const std::string& strFileName) const
{
	size_t nFildPos = strFileName.rfind(".");
	if (nFildPos == std::string::npos)
	{
		return "";
	}

	std::string strfileSuffix = strFileName.substr(strFileName.rfind(".") + 1, strFileName.size());
	return strfileSuffix;
}

