#include "Asset/HrMaterial.h"

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
	m_ambient = HrMath::MakeColor(255, 244, 214, 255).Value();
	m_diffuse = HrMath::MakeColor(255, 244, 214, 255).Value();
	m_specular = HrMath::MakeColor(255, 244, 214, 255).Value();
	m_emissive = HrMath::MakeColor(255, 244, 214, 255).Value();

	m_fOpacity = 1.0f;
}
