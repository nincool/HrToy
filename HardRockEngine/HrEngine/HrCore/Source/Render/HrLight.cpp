#include "Render/HrLight.h"

using namespace Hr;

HrLight::HrLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;

	m_fRange = 100000;

	m_fAttenuation0 = 1.0f;
	m_fAttenuation1 = 0.0f;
	m_fAttenuation2 = 0.0f;
}

HrLight::~HrLight()
{

}

HrLight::EnumLightType HrLight::LightType()
{
	return m_lightType;
}


void HrLight::SetDirection(const Vector3& v3Direction)
{
	m_v3Direction = v3Direction;
}

void HrLight::SetAttenuation(float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
{
	m_fRange = fRange;
	m_fAttenuation0 = fAttenuation0;
	m_fAttenuation1 = fAttenuation1;
	m_fAttenuation2 = fAttenuation2;
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

float HrLight::GetAttenuationRange() const
{
	return m_fRange;
}

float HrLight::GetAttenuation0() const
{
	return m_fAttenuation0;
}

float HrLight::GetAttenuation1() const
{
	return m_fAttenuation1;
}

float HrLight::GetAttenuation2() const
{
	return m_fAttenuation2;
}

void HrLight::SetPosition(const Vector3& vPosition)
{
	m_v3Position = vPosition;
}

const Vector3& HrLight::GetPosition() const
{
	return m_v3Position;
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////


HrAmbientLight::HrAmbientLight()
{
	m_lightType = HrLight::LT_AMBIENT;
	m_diffuse = HrColor(0.5f, 0.5f, 0.5f, 1.0f);
}

HrAmbientLight::HrAmbientLight(const HrColor& ambient)
{
	m_lightType = HrLight::LT_AMBIENT;
	m_diffuse = ambient;
}


///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrDirectionalLight::HrDirectionalLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;
	m_v3Direction = Vector3(1.0f, -1.0f, 1.0f);
	m_diffuse = HrMath::MakeColor(200.0f, 200.0f, 200.0f, 255.0f);
	m_specular = HrMath::MakeColor(255.0f, 244.0f, 215.0f, 255.0f);
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

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
HrPointLight::HrPointLight()
{
	m_lightType = HrLight::LT_POINT;
}

HrPointLight::HrPointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
{
	m_lightType = HrLight::LT_POINT;

	m_diffuse = diffuse;
	m_specular = specular;
	m_fRange = fRange;
	m_fAttenuation0 = fAttenuation0;
	m_fAttenuation1 = fAttenuation1;
	m_fAttenuation2 = fAttenuation2;
}

HrPointLight::~HrPointLight()
{
}
