#include "Scene/HrSceneObjectComponent.h"

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

