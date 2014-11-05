#include "HrMaterial.h"

using namespace HR;

CHrMaterial::CHrMaterial()
{
	ResetMaterial();
}

CHrMaterial::~CHrMaterial()
{

}

D3DMATERIAL9* HR::CHrMaterial::GetMaterial()
{
	return &m_stD3DMaterial;
}

void CHrMaterial::ResetMaterial()
{
	::ZeroMemory(&m_stD3DMaterial, sizeof(m_stD3DMaterial));
}

void CHrMaterial::SetDiffuseColor(D3DXCOLOR color)
{
	m_stD3DMaterial.Diffuse.r = color.r;
	m_stD3DMaterial.Diffuse.g = color.g;
	m_stD3DMaterial.Diffuse.b = color.b;
	m_stD3DMaterial.Diffuse.a = color.a;
}

void CHrMaterial::SetAmbientColor(D3DXCOLOR color)
{
	m_stD3DMaterial.Ambient.r = color.r;
	m_stD3DMaterial.Ambient.g = color.g;
	m_stD3DMaterial.Ambient.b = color.b;
	m_stD3DMaterial.Ambient.a = color.a;
}

void CHrMaterial::SetSpecularColor(D3DXCOLOR color)
{
	m_stD3DMaterial.Specular.r = color.r;
	m_stD3DMaterial.Specular.g = color.g;
	m_stD3DMaterial.Specular.b = color.b;
	m_stD3DMaterial.Specular.a = color.a;
}

void CHrMaterial::SetEmissiveColor(D3DXCOLOR color)
{
	m_stD3DMaterial.Emissive.r = color.r;
	m_stD3DMaterial.Emissive.g = color.g;
	m_stD3DMaterial.Emissive.b = color.b;
	m_stD3DMaterial.Emissive.a = color.a;
}

void CHrMaterial::SetPower(float fPower)
{
	m_stD3DMaterial.Power = fPower;
}

