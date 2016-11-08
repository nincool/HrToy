#include "HrCore/Include/Scene/HrTransform.h"
#include "HrCore/Include/Scene/HrSceneNode.h"

using namespace Hr;

HrTransform::HrTransform(HrSceneNode* pSceneNode)
{
	m_pSceneNode = pSceneNode;
}

void HrTransform::SetPosition(const Vector3& v3Pos)
{
	m_vWordPosition = v3Pos;

	m_pSceneNode->DirtyTransform();
}

void HrTransform::SetPosition(REAL x, REAL y, REAL z)
{
	Vector3 v(x, y, z);
	SetPosition(v);

	m_pSceneNode->DirtyTransform();
}

const Vector3& HrTransform::GetPosition()
{
	return m_vWordPosition;
}

void HrTransform::SetLocalPosition(const Vector3& v3Pos)
{
	m_pSceneNode->DirtyTransform();
}

const Vector3& HrTransform::GetLocalPosition()
{
	return m_vLocalPosition;
}

void HrTransform::SetLocalPosition(REAL x, REAL y, REAL z)
{
	m_pSceneNode->DirtyTransform();
}

void HrTransform::Translate(const Vector3& v3)
{
	m_vWordPosition += v3;
	
	m_pSceneNode->DirtyTransform();
}

void HrTransform::Roll(const Radian& angle, EnumTransformSpace relative /*= TS_LOCAL*/)
{

}

void HrTransform::Pitch(const Radian& angle, EnumTransformSpace relative /*= TS_LOCAL*/)
{

}

void HrTransform::Yaw(const Radian& angle, EnumTransformSpace relative /*= TS_LOCAL*/)
{

}

void HrTransform::Rotate(const Vector3& axis, const Radian& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}

void HrTransform::Rotate(const Quaternion& q, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}
