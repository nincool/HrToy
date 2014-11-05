#include "HrLight.h"


using namespace HR;
CHrLight::CHrLight()
{
	ResetLight();
}

CHrLight::~CHrLight()
{
}

D3DLIGHT9* CHrLight::GetLight()
{
	return &m_stLight;
}

void CHrLight::SetLightType(D3DLIGHTTYPE lightType)
{
	m_stLight.Type = lightType;
}

void CHrLight::ResetLight()
{
	::ZeroMemory(&m_stLight, sizeof(m_stLight));
	SetLightType(D3DLIGHT_DIRECTIONAL);
	SetDiffuseColor(D3DCOLOR_ARGB(0, 0, 0, 0));
	SetAmbientColor(D3DCOLOR_ARGB(0, 0, 0, 0));
	SetSpecularColor(D3DCOLOR_ARGB(0, 0, 0, 0));
	
	SetLightPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetLightDirection(D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void CHrLight::SetDiffuseColor(D3DXCOLOR color)
{
	m_stLight.Diffuse.r = color.r;
	m_stLight.Diffuse.g = color.g;
	m_stLight.Diffuse.b = color.b;
	m_stLight.Diffuse.a = color.a;
}

void CHrLight::SetAmbientColor(D3DXCOLOR color)
{
	m_stLight.Ambient.r = color.r;
	m_stLight.Ambient.g = color.g;
	m_stLight.Ambient.b = color.b;
	m_stLight.Ambient.a = color.a;
}

void CHrLight::SetSpecularColor(D3DXCOLOR color)
{
	m_stLight.Specular.r = color.r;
	m_stLight.Specular.g = color.g;
	m_stLight.Specular.b = color.b;
	m_stLight.Specular.a = color.a;
}

void CHrLight::SetRange(float fRange)
{
	m_stLight.Range = fRange;
}

void CHrLight::SetLightPosition(D3DVECTOR vPos)
{
	m_stLight.Position = vPos;
}

void CHrLight::SetLightDirection(D3DVECTOR vDirection)
{
	m_stLight.Direction = vDirection;
}






































