#include "Asset/HrMaterial.h"

using namespace Hr;

HrMaterial::HrMaterial()
{
	m_fOpacity = 0.0f;
	m_fPower = 0.0f;
}

HrMaterial::~HrMaterial()
{

}

void HrMaterial::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{

}

bool HrMaterial::LoadImpl()
{
	return true;
}

bool HrMaterial::UnloadImpl()
{
	return true;
}
