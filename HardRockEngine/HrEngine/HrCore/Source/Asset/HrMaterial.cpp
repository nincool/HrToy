#include "Asset/HrMaterial.h"
#include "Asset/HrColor.h"

using namespace Hr;

HrMaterial::HrMaterial()
{
	m_fOpacity = 0.0f;
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

void HrMaterial::BuildToDefultMaterial()
{
	m_ambient = HrColor::F4Black;
	m_diffuse = HrColor::F4Black;
	m_specular = HrColor::F4Black;
	m_emissive = HrColor::F4Magenta;

	m_fOpacity = 1.0f;
}
