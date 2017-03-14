#include "Render/HrLight.h"
#include "Scene/HrEntityNode.h"

using namespace Hr;

HrLight::HrLight()
{
	m_lightType = HrLight::LT_DIRECTIONAL;

	m_fRange = 100000;

	m_fAttenuation0 = 1.0f;
	m_fAttenuation1 = 0.0f;
	m_fAttenuation2 = 0.0f;

	m_pAttachNode = nullptr;
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

void HrLight::AttachLightNode(HrLightNode* pLightNode)
{
	m_pAttachNode = pLightNode;
}

HrLightNode* HrLight::GetAttachLightNode() const
{
	return m_pAttachNode;
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
