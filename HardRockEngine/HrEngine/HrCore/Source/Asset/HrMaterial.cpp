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

void HrMaterial::FillMaterialInfo(const float4& ambient, const float4& diffuse, const float4& specular, const float4& emissive, float fOpacity)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_emissive = emissive;
	m_fOpacity = fOpacity;
}

const float4& HrMaterial::GetAmbient() const
{
	return m_ambient;
}

const float4& HrMaterial::GetDiffuse() const
{
	return m_diffuse;
}

const float4& HrMaterial::GetSpecular() const
{
	return m_specular;
}

const float4& HrMaterial::GetEmissive() const
{
	return m_emissive;
}

float HrMaterial::GetOpacity() const
{
	return m_fOpacity;
}
