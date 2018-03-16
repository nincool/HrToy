#include "Scene/HrSceneObjectComponent.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrSceneObjectComponent::HrSceneObjectComponent(const std::string& strName) : m_strName(strName)
{

}

HrSceneObjectComponent::~HrSceneObjectComponent()
{

}

bool HrSceneObjectComponent::InitComponent()
{
	return true;
}

bool HrSceneObjectComponent::Update(float fDelta)
{
	return true;
}

const std::string& HrSceneObjectComponent::GetName()
{
	return m_strName;
}

HrSceneObjectComponent::EnumSceneComponentType HrSceneObjectComponent::GetComType()
{
	return m_comType;
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
HrCameraComponet::HrCameraComponet(const std::string& strName) : HrSceneObjectComponent(strName)
{
	m_comType = HrSceneObjectComponent::SCT_CAMERA;
	m_pCamera = HrMakeSharedPtr<HrCamera>(strName);
}

HrCameraComponet::~HrCameraComponet()
{
	
}

const HrCameraPtr& HrCameraComponet::GetCamera()
{
	return m_pCamera;
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
HrLightComponent::HrLightComponent(const std::string& strName, HrLight::EnumLightType lightType) : HrSceneObjectComponent(strName)
{
	m_comType = HrSceneObjectComponent::SCT_LIGHT;

	switch (lightType)
	{
	case HrLight::LT_AMBIENT:
		m_pLight = HrMakeSharedPtr<HrAmbientLight>();
		break;
	case HrLight::LT_DIRECTIONAL:
		m_pLight = HrMakeSharedPtr<HrDirectionalLight>();
		break;
	case HrLight::LT_POINT:
		break;
	case HrLight::LT_SPOTLIGHT:
		break;
	}
}

HrLightComponent::~HrLightComponent()
{

}

const HrLightPtr& HrLightComponent::GetLight()
{
	return m_pLight;
}

