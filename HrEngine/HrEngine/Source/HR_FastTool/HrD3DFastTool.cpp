#include "HrD3DFastTool.h"
#include "../HR_Material/HrMaterial.h"
#include "../HR_Light/HrLight.h"

using namespace HR;

CHrD3DFastTool CHrD3DFastTool::m_s_hrD3DFastTool;
CHrD3DFastTool::CHrD3DFastTool()
{
}


CHrD3DFastTool::~CHrD3DFastTool()
{
}

CHrMaterial* CHrD3DFastTool::CreateMaterial(_HR_MATERIAL_ eMaterialType)
{
	CHrMaterial* pMaterial = new CHrMaterial();
	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	switch (eMaterialType)
	{
	case MATERIAL_RED:
	{
		color = D3DCOLOR_ARGB(255, 150, 0, 0);
		break;
	}
	case MATERIAL_GREEN:
	{
		color = D3DCOLOR_ARGB(255, 0, 150, 0);
		break;
	}
	case MATERIAL_BLUE:
	{
		color = D3DCOLOR_ARGB(255, 0, 0, 150);
		break;
	}
	case MATERIAL_WHITE:
	{
		color = D3DCOLOR_ARGB(255, 255, 255, 255);
		break;
	}
	default:
		break;
	}
	
	pMaterial->SetAmbientColor(color);
	pMaterial->SetDiffuseColor(color);
	pMaterial->SetSpecularColor(color);
	pMaterial->SetPower(5.0f);

	return pMaterial;
}

CHrLight* CHrD3DFastTool::CreateLight(_HR_DIRECTLIGHT_ eLightType)
{
	CHrLight* pMyLight = new CHrLight();
	D3DXCOLOR colorAmbient = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DXCOLOR colorDiffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	D3DXCOLOR colorSpecular = D3DCOLOR_ARGB(255, 255, 255, 255);
	switch (eLightType)
	{
	case _HR_DIRECTLIGHT_::LIGHT_RED:
	{
		colorAmbient = D3DCOLOR_ARGB(255, 50, 0, 0);
		colorDiffuse = D3DCOLOR_ARGB(255, 255, 0, 0);
		colorSpecular = D3DCOLOR_ARGB(255, 255, 0, 0);
		pMyLight->SetLightType(D3DLIGHT_DIRECTIONAL);
		break;
	}
	case _HR_DIRECTLIGHT_::LIGHT_GREEN:
	{
		colorAmbient = D3DCOLOR_ARGB(255, 0, 50, 0);
		colorDiffuse = D3DCOLOR_ARGB(255, 0, 255, 0);
		colorSpecular = D3DCOLOR_ARGB(255, 0, 255, 0);
		pMyLight->SetLightType(D3DLIGHT_DIRECTIONAL);
		break;
	}
	case _HR_DIRECTLIGHT_::LIGHT_BLUE:
	{
		colorAmbient = D3DCOLOR_ARGB(255, 0, 0, 50);
		colorDiffuse = D3DCOLOR_ARGB(255, 0, 0, 255);
		colorSpecular = D3DCOLOR_ARGB(255, 0, 0, 255);
		pMyLight->SetLightType(D3DLIGHT_DIRECTIONAL);
		break;
	}
	case _HR_DIRECTLIGHT_::LIGHT_WHITE:
	{
		colorAmbient = D3DCOLOR_ARGB(255, 50, 50, 50);
		colorDiffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
		colorSpecular = D3DCOLOR_ARGB(255, 200, 200, 200);
		break;
	}
	case _HR_DIRECTLIGHT_::LIGHT_DARK:
	{
		colorAmbient = D3DCOLOR_ARGB(255, 30, 30, 30);
		colorDiffuse = D3DCOLOR_ARGB(255, 30, 30, 30);
		colorSpecular = D3DCOLOR_ARGB(255, 30, 30, 30);
		break;
	}
	default:
		break;
	}

	pMyLight->SetAmbientColor(colorAmbient);
	pMyLight->SetDiffuseColor(colorDiffuse);
	pMyLight->SetSpecularColor(colorSpecular);
	pMyLight->SetLightPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMyLight->SetLightDirection(D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	return pMyLight;
}

CHrD3DFastTool* CHrD3DFastTool::Instance()
{
	return &m_s_hrD3DFastTool;
}




