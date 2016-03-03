#include "HrCore/Include/Asset/HrResourceLoader.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include <fstream>

using namespace Hr;

void HrResourceLoader::LoadFromFile(std::string strFilePath, HrStreamData& data)
{
	std::fstream fileData(strFilePath.c_str(), std::ios::ate);
	uint64 nDataLength = fileData.tellg();
	void* pBuffer = data.ResizeBuffer(nDataLength);

	fileData.read((char*)pBuffer, nDataLength);
	fileData.close();
}
