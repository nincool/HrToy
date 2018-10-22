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

void HrLight::SetColor(const HrColor& color)
{
	m_lightColor = color;
}

const HrColor& HrLight::GetColor() const
{
	return m_lightColor;
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////


HrAmbientLight::HrAmbientLight()
{
	m_lightType = HrLight::LT_AMBIENT;
	m_lightColor = HrColor(0.1f, 0.1f, 0.1f, 1.0f);
}

HrAmbientLight::HrAmbientLight(const HrColor& ambient)
{
	m_lightType = HrLight::LT_AMBIENT;
	m_lightColor = ambient;
}


///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrDirectionalLight::HrDirectionalLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;
	m_v3Direction = Vector3(1.0f, -1.0f, 1.0f);
	m_lightColor = HrMath::MakeColor(240.0f, 240.0f, 240.0f, 255.0f);

}

HrDirectionalLight::HrDirectionalLight(const Vector3 v3Direction, const HrColor& lightColor)
{
	m_lightType = HrLight::LT_DIRECTIONAL;
	
	m_v3Direction = v3Direction;
	m_lightColor = lightColor;

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
	
	m_lightColor = HrMath::MakeColor(200.0f, 200.0f, 200.0f, 255.0f);
	m_fRange = 200;
	m_fAttenuation0 = 0.01;	//常数衰减
	m_fAttenuation1 = 0.001; //线性衰减系数
	m_fAttenuation2 = 0.00001; //2次方 急速衰减
	m_v3Position = Vector3(0.0f, 0.0f, -60.0f);
}

HrPointLight::HrPointLight(const HrColor& lightColor, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
{
	m_lightType = HrLight::LT_POINT;

	m_lightColor = lightColor;
	m_fRange = fRange;
	m_fAttenuation0 = fAttenuation0;
	m_fAttenuation1 = fAttenuation1;
	m_fAttenuation2 = fAttenuation2;
}

HrPointLight::~HrPointLight()
{
}
