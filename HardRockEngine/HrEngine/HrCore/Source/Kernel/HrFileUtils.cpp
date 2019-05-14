#include "Kernel/HrFileUtils.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrLog.h"
#include <fstream>

using namespace Hr;
using namespace std::experimental;

std::string HrFileUtils::m_s_strSeparator = "\\";

HrFileUtils::HrFileUtils()
{
	char cBuf[MAX_PATH];
	::GetModuleFileNameA(nullptr, cBuf, sizeof(cBuf));
	std::string strAppPath = cBuf;

	m_strAppPath = strAppPath.substr(0, strAppPath.rfind(m_s_strSeparator));
	std::string strAssetPath = m_strAppPath.substr(0, m_strAppPath.rfind(m_s_strSeparator));
	m_strMediaPath = strAssetPath + "\\Media\\";

	AddSearchDirectory(m_strAppPath += "\\");
	AddSearchDirectory(strAssetPath + "\\");
	AddSearchDirectory(m_strMediaPath);
	AddSearchDirectory(strAssetPath + "\\Media\\Model\\");
	AddSearchDirectory(strAssetPath + "\\Media\\Scene\\");
	AddSearchDirectory(strAssetPath + "\\Media\\Effect\\Hlsl\\");
	AddSearchDirectory(strAssetPath + "\\Media\\Prefab\\");
	AddSearchDirectory(strAssetPath + "\\Media\\Texture\\");
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
		filesystem::path fileFullPath;
		for (auto& item : m_vecSearchDirectorys)
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
	return m_strAppPath;
}

std::string HrFileUtils::GetAppPath() const
{
	return m_strAppPath;
}

std::string HrFileUtils::GetFileString(const std::string& strFile)
{
	std::string strFullPath = GetFullPathForFileName(strFile);
	if (strFullPath.empty())
	{
		return "";
	}

	std::fstream fileStream(strFullPath.c_str(), std::ios::in);
	BOOST_ASSERT(fileStream.is_open());
	std::istreambuf_iterator<char> beg(fileStream), end;
	std::string strContent(beg, end);
	fileStream.close();

	return strContent;
}

HrStreamDataPtr HrFileUtils::GetFileData(const std::string& strFile)
{
	HrStreamDataPtr pFileStream = std::make_shared<HrStreamData>();

	std::string strFullPath = GetFullPathForFileName(strFile);
	if (strFullPath.empty())
	{
		return pFileStream;
	}

	std::fstream fileStream(strFullPath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	BOOST_ASSERT(fileStream.is_open());
	std::uint64_t nFileLength = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);

	size_t nLength = static_cast<size_t>(nFileLength);
	pFileStream->ResizeBuffer(nLength);
	fileStream.read(reinterpret_cast<char*>(pFileStream->GetBufferPoint()), nLength);
	fileStream.close();

	return pFileStream;
}

void HrFileUtils::AddSearchDirectory(const std::string& strPath)
{
	if (filesystem::exists(strPath))
	{
		m_vecSearchDirectorys.emplace_back(filesystem::path(strPath));
	}
	else
	{
		HRERROR("HrFileUtil AddSearchDirectory Error! [%s]", strPath.c_str());
	}
}

std::string HrFileUtils::GetFileSuffix(const std::string& strFile) const
{
	size_t nFildPos = strFile.rfind(".");
	if (nFildPos == std::string::npos)
	{
		return "";
	}

	std::string strfileSuffix = strFile.substr(strFile.rfind(".") + 1, strFile.size());
	return strfileSuffix;
}

std::string HrFileUtils::ReplaceFileName(const std::string& strFile, const std::string& strName) const
{
	size_t nFildPos = strFile.rfind("\\");
	if (nFildPos == std::string::npos)
	{
		return std::string(strFile + "\\" + strName);
	}
	return std::string(strFile.substr(0, nFildPos) + "\\" + strName);
}

std::string HrFileUtils::GetFileNameWithSuffix(const std::string& strFile) const
{
	size_t nFileNamePos = strFile.rfind("\\");

	if (nFileNamePos == std::string::npos)
	{
		return strFile;
	}
	else
	{
		return strFile.substr(nFileNamePos + 1, strFile.size()-1);
	}
}

std::string HrFileUtils::GetFilePath(const std::string& strFile) const
{
	size_t nFilePos = strFile.rfind("\\");
	if (nFilePos == std::string::npos)
	{
		return strFile;
	}
	return strFile.substr(0, nFilePos);
}

std::string HrFileUtils::GetFileName(const std::string& strFile) const
{
	size_t nFileNamePos = strFile.rfind("\\");
	size_t nSuffixPos = strFile.rfind(".");
	if (nFileNamePos == std::string::npos)
	{
		if (nSuffixPos == std::string::npos)
		{
			return strFile;
		}
		else
		{
			return strFile.substr(0, nSuffixPos);
		}
	}
	else
	{
		if (nSuffixPos == std::string::npos)
		{
			return strFile.substr(nFileNamePos + 1, strFile.size()-nFileNamePos-1);
		}
		else
		{
			return strFile.substr(nFileNamePos + 1, nSuffixPos - nFileNamePos-1);
		}
	}
}

bool HrFileUtils::WriteDataToFile(const std::string& strFile, const std::string& strData)
{
	std::fstream fileStream(strFile.c_str(), std::ios::out | std::ios::trunc);
	fileStream.write(strData.c_str(), strData.size());
	bool bGood = fileStream.good();
	fileStream.close();

	return bGood;
}

bool HrFileUtils::WriteDataToFile(const std::string& strFile, const HrStreamDataPtr& pStreamData)
{
	return true;
}

std::string HrFileUtils::GetMediaPath() const
{
	return m_strMediaPath;
}

