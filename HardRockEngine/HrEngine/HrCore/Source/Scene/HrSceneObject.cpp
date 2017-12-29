#include "Scene/HrSceneObject.h"

using namespace Hr;

HrSceneObject::HrSceneObject()
{
}

HrSceneObject::HrSceneObject(const std::string& strName)
{
	m_strName = strName;
}

HrSceneObject::HrSceneObject(const std::string& strName, const HrRenderablePtr& pRenderable)
{
	m_strName = strName;
	m_pRenderable = pRenderable;
}

HrSceneObject::~HrSceneObject()
{
}

void HrSceneObject::SetName(const std::string& strName)
{
	m_strName = strName;
}

const std::string& HrSceneObject::GetName()
{
	return m_strName;
}

void HrSceneObject::AttachRenderable(const HrRenderablePtr& pRenderable)
{
	if (!m_pRenderable)
	{
		BOOST_ASSERT(false);
	}

	m_pRenderable = pRenderable;
}

const HrRenderablePtr& HrSceneObject::GetRenderable()
{
	return m_pRenderable;
}


