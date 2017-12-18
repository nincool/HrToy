#include "HrCore/Include/Scene/HrTransform.h"
#include "HrCore/Include/Scene/HrSceneNode.h"

using namespace Hr;

HrTransform::HrTransform(HrSceneNode* pSceneNode)
{
	m_bDirtyTransform = true;

	m_pSceneNode = pSceneNode;
	m_vScale = Vector3(1.0f, 1.0f, 1.0f);
	m_orientation = Quaternion::Identity();

	Rotate(m_orientation);
}

void HrTransform::SetPosition(const Vector3& v3Pos)
{
	m_vPosition = v3Pos;
	DirtyTransform();
}

void HrTransform::SetPosition(REAL x, REAL y, REAL z)
{
	SetPosition(Vector3(x, y, z));
	DirtyTransform();
}

const Vector3& HrTransform::GetPosition()
{
	return m_vPosition;
}

void HrTransform::SetRotation(const Vector3& angle)
{
	SetOrientation(HrMath::RotationQuaternionPitchYawRoll(HrMath::Degree2Radian(angle)));
}

const Quaternion& HrTransform::GetOrientation() const
{
	return m_orientation;
}

void HrTransform::SetOrientation(const Quaternion& orientation)
{
	m_orientation = orientation;
}

const Vector3& HrTransform::GetForward() const
{
	return m_vForward;
}

const Vector3& HrTransform::GetRight() const
{
	return m_vRight;
}

const Vector3& HrTransform::GetUp() const
{
	return m_vUp;
}

void HrTransform::Translate(const Vector3& v3, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{
	switch (relativeTo)
	{
	case TS_LOCAL:
		m_vPosition += v3;
		break;
	case TS_WORLD:
		break;
	case TS_PARENT:
		break;
	}
	
	DirtyTransform();
}

void HrTransform::Roll(const Radian& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}

void HrTransform::Pitch(const Radian& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}

void HrTransform::Yaw(const Radian& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}

void HrTransform::Rotate(const Vector3& axis, const Radian& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{

}

void HrTransform::Rotate(const Vector3& angle, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{
	Rotate(HrMath::RotationQuaternionPitchYawRoll(HrMath::Degree2Radian(angle)), relativeTo);
}

void HrTransform::Rotate(const Quaternion& q, EnumTransformSpace relativeTo /*= TS_LOCAL*/)
{
	switch (relativeTo)
	{
	case TS_LOCAL:
		m_orientation = m_orientation * q;
		break;
	case TS_WORLD:
		break;
	case TS_PARENT:
		break;
	}

	m_orientation = HrMath::Normalize(m_orientation);
	Matrix4 matOrientation = HrMath::ToMatrix(m_orientation);
	
	Vector4 vRight = matOrientation.Row(0);
	m_vRight = Vector3(vRight.x(), vRight.y(), vRight.z());
	
	Vector4 vUp = matOrientation.Row(1);
	m_vUp = Vector3(vUp.x(), vUp.y(), vUp.z());

	Vector4 vForward = matOrientation.Row(2);
	m_vForward = Vector3(vForward.x(), vForward.y(), vForward.z());
	
	DirtyTransform();
}

const Vector3& HrTransform::GetWorldScale()
{
	if (m_bDirtyTransform)
	{
		BOOST_ASSERT(m_pSceneNode);
		if (m_pSceneNode->GetParent() != nullptr)
		{
			const Vector3& parentWorldScale = m_pSceneNode->GetParent()->GetTransform()->GetWorldScale();
			m_vWorldScale = parentWorldScale * m_vScale;
		}
		else
		{
			m_vWorldScale = m_vScale;
		}
	}

	return m_vWorldScale;
}

const Quaternion& HrTransform::GetWorldOriention()
{
	if (m_bDirtyTransform)
	{
		BOOST_ASSERT(m_pSceneNode);
		if (m_pSceneNode->GetParent() != nullptr)
		{
			const Quaternion& parentOriention = m_pSceneNode->GetParent()->GetTransform()->GetWorldOriention();
			m_worldOriention = parentOriention * m_orientation;
		}
		else
		{
			m_worldOriention = m_orientation;
		}
	}

	return m_worldOriention;
}

const Vector3& HrTransform::GetWorldPosition()
{
	if (m_bDirtyTransform)
	{
		BOOST_ASSERT(m_pSceneNode);
		if (m_pSceneNode->GetParent() != nullptr)
		{
			const Vector3& parentPosition = m_pSceneNode->GetParent()->GetTransform()->GetWorldPosition();
			m_vWorldPosition = m_vPosition;
			m_vWorldPosition += parentPosition;
		}
		else
		{
			m_vWorldPosition = m_vPosition;
		}
	}

	return m_vWorldPosition;
}

const Matrix4& HrTransform::GetWorldMatrix()
{
	if (m_bDirtyTransform)
	{
		m_matWorldMatrix = std::move(HrMath::MakeTransform(GetWorldPosition(), GetWorldScale(), GetWorldOriention()));
		m_bDirtyTransform = false;
	}

	return m_matWorldMatrix;
}

void HrTransform::UpdateFromParent()
{
	//Update orientation
	if (m_pSceneNode != nullptr)
	{
		m_pSceneNode->GetTransform()->GetWorldScale();
	}
}

void HrTransform::DirtyTransform()
{
	m_bDirtyTransform = true;
	m_pSceneNode->DirtyTransform();
}

void HrTransform::SetScale(const Vector3& v3Scale)
{
	m_vScale = v3Scale;
	m_bDirtyTransform = true;
}

const Vector3& HrTransform::GetScale()
{
	return m_vScale;
}

