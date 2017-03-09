#include "Render/HrLight.h"

using namespace Hr;

HrLight::HrLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;
}

HrLight::~HrLight()
{

}

HrLight::EnumLightType HrLight::LightType()
{
	return m_lightType;
}


void Hr::HrLight::SetDirection(const Vector3& v3Direction)
{
	m_v3Direction = v3Direction;
}

const Vector3& HrLight::GetDirection() const
{
	return m_v3Direction;
}
void HrLight::SetDiffuse(const HrColor& diffuse)
{
	m_diffuse = diffuse;
}

const HrColor& HrLight::GetDiffuse() const
{
	return m_diffuse;
}

void HrLight::SetSpecular(const HrColor& specular)
{
	m_specular = specular;
}

const HrColor& HrLight::GetSpecular() const
{
	return m_specular;
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrDirectionalLight::HrDirectionalLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;
}

HrDirectionalLight::HrDirectionalLight(const Vector3 v3Direction, const HrColor& diffuse, const HrColor& specular)
{
	m_lightType = HrLight::LT_DIRECTIONAL;
	m_v3Direction = v3Direction;
	m_diffuse = diffuse;
	m_specular = specular;
}

HrDirectionalLight::~HrDirectionalLight()
{

}
