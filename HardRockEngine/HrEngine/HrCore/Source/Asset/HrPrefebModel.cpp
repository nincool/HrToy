#include "Asset/HrPrefebModel.h"
#include "HrUtilTools/Include/HrUtil.h"


using namespace Hr;

HrPrefebModel::HrPrefebModel()
{

}

HrPrefebModel::~HrPrefebModel()
{

}

void HrPrefebModel::DeclareResource(std::string& strFilePath, std::string& strFileName)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MODEL;

	m_nHashID = HrHashValue(m_strFilePath);
}

void HrPrefebModel::Load()
{

}

void HrPrefebModel::Unload()
{

}
