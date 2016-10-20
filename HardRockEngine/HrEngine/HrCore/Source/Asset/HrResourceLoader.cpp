#include "Asset/HrResourceLoader.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include <fstream>

using namespace Hr;

bool HrResourceLoader::LoadFromFile(std::string strFilePath, HrStreamData& data)
{
	std::fstream fileData(strFilePath.c_str(), std::ios::ate | std::ios::in);
	int64 nDataLength = fileData.tellg();
	if (nDataLength == -1)
	{
		return false;
	}
	fileData.seekg(std::ios::beg);
	void* pBuffer = data.ResizeBuffer(nDataLength);

	fileData.read((char*)pBuffer, nDataLength);
	fileData.close();

	return true;
}
