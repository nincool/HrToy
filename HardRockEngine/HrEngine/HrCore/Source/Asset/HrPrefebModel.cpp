#include "Asset/HrPrefebModel.h"
#include "Asset/Loader/HrModelLoader.h"
#include "Asset/Loader/HrFBXLoader.h"
#include "Kernel/HrFileUtils.h"
#include "HrUtilTools/Include/HrUtil.h"


using namespace Hr;
using namespace std;

HrPrefebModel::HrPrefebModel()
{

}

HrPrefebModel::~HrPrefebModel()
{

}

void HrPrefebModel::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MODEL;

	m_nHashID = HrHashValue(m_strFilePath);
}

void HrPrefebModel::Load()
{
	HrModelLoaderPtr pModelLoader = std::make_shared<HrModelLoader>();
	pModelLoader->Load(m_strFilePath);
}

void HrPrefebModel::Unload()
{

}
