#include "Scene/HrTransform.h"
#include "Scene/HrSceneNode.h"

using namespace Hr;

Vector3 HrTransform::m_s_v3Zero = Vector3(0, 0, 0);
Vector3 HrTransform::m_s_v3One = Vector3(1, 1, 1);
Quaternion HrTransform::m_s_quaIdentity = Quaternion::Identity();

HrTransform::HrTransform(HrSceneNode* pSceneNode)
{
	m_pSceneNode = pSceneNode;

	m_bDirtyTransform
		= m_bDirtyWorldScale
		= m_bDirtyWorldOriention
		= m_bDirtyWorldPosition
		= m_bDirtyWorldMatrix = true;

	m_bDirtyAABBox = true;

	m_vPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_vScale = Vector3(1.0f, 1.0f, 1.0f);
	m_orientation = Quaternion::Identity();
	m_vEulerAngles = Vector3::Zero();

	m_localAABBox = m_worldAABBox = AABBox(Vector3::Zero(), Vector3::Zero());

	Rotate(m_orientation);

}

void HrTransform::SetPosition(const Vector3& v3Pos)
{
	m_vPosition = v3Pos;
	DirtyTransform(true);
}

void HrTransform::SetPosition(REAL x, REAL y, REAL z)
{
	SetPosition(Vector3(x, y, z));
}

const Vector3& HrTransform::GetPosition()
{
	return m_vPosition;
}

void HrTransform::SetRotation(const Vector3& angle)
{
	m_vEulerAngles = angle;
	DecomposeOriention(HrMath::RotationQuaternionPitchYawRoll(HrMath::Degree2Radian(angle)));
}

const Quaternion& HrTransform::GetOrientation() const
{
	return m_orientation;
}

void HrTransform::SetOrientation(const Quaternion& orientation)
{
	DecomposeOriention(orientation);
	m_vEulerAngles = HrMath::Radian2Degree(HrMath::ToPitchYawRoll(m_orientation));
}

void HrTransform::DecomposeOriention(const Quaternion& orientation)
{
	m_orientation = HrMath::Normalize(orientation);

	Matrix4 matOrientation = HrMath::ToMatrix(m_orientation);

	Vector4 vRight = matOrientation.Row(0);
	m_vRight = Vector3(vRight.x(), vRight.y(), vRight.z());

	Vector4 vUp = matOrientation.Row(1);
	m_vUp = Vector3(vUp.x(), vUp.y(), vUp.z());

	Vector4 vForward = matOrientation.Row(2);
	m_vForward = Vector3(vForward.x(), vForward.y(), vForward.z());

	DirtyTransform(true, false, true);
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
		m_vPosition += HrMath::TransformQuat(v3, m_orientation);
		break;
	case TS_WORLD:
		if (m_pSceneNode)
		{
			//v3 表示为世界坐标系下的位移，所以需要转换为父节点坐标系下的位移
			m_vPosition += ConvertWorldToLocalDirection(v3);
		}
		break;
	case TS_PARENT:
		m_vPosition += v3;
		break;
	}
	DirtyTransform(true);
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

	SetOrientation(m_orientation);
}

const Vector3& HrTransform::GetWorldScale()
{
	if (m_bDirtyWorldScale)
	{
		if (m_pSceneNode->GetParent())
		{
			const Vector3& parentWorldScale = m_pSceneNode->GetParent()->GetTransform()->GetWorldScale();
			m_vWorldScale = parentWorldScale * m_vScale;
		}
		else
		{
			m_vWorldScale = m_vScale;
		}

		m_bDirtyWorldScale = false;
	}

	return m_vWorldScale;
}

const Quaternion& HrTransform::GetWorldOriention()
{
	if (m_bDirtyWorldOriention)
	{
		if (m_pSceneNode->GetParent())
		{
			const Quaternion& parentOriention = GetParentOriention();
			m_worldOriention = parentOriention * m_orientation;
		}
		else
		{
			m_worldOriention = m_orientation;
		}

		m_bDirtyWorldOriention = false;
	}

	return m_worldOriention;
}

const Vector3& HrTransform::GetWorldPosition()
{
	if (m_bDirtyWorldPosition)
	{
		if (m_pSceneNode->GetParent())
		{			
			const Vector3& parentScale = GetParentScale();
			const Quaternion& parentOriention = GetParentOriention();
			m_vWorldPosition = HrMath::TransformQuat(parentScale * m_vPosition, parentOriention);
			m_vWorldPosition += GetParentPosition();
		}
		else
		{
			m_vWorldPosition = m_vPosition;
		}

		m_bDirtyWorldPosition = false;
	}

	return m_vWorldPosition;
}

const Matrix4& HrTransform::GetWorldMatrix()
{
	if (m_bDirtyWorldMatrix)
	{
		m_matWorldMatrix = std::move(HrMath::MakeTransform(GetWorldPosition(), GetWorldScale(), GetWorldOriention()));
		m_bDirtyWorldMatrix = false;
	}

	return m_matWorldMatrix;
}

void HrTransform::SetScale(const Vector3& v3Scale)
{
	m_vScale = v3Scale;
	DirtyTransform(false, true);
}

const Vector3& HrTransform::GetScale()
{
	return m_vScale;
}

bool HrTransform::GetTransformDirty()
{
	return m_bDirtyTransform;
}

void HrTransform::SetTransformDirty(bool bDirty)
{
	m_bDirtyTransform = bDirty;
}

void HrTransform::UpdateTransform(float fDelta)
{
	HR_UNUSED(fDelta);
}

void HrTransform::DirtyTransform(bool bDirtyPos, bool bDirtyScale, bool bDirtyOrientation)
{
	if (bDirtyPos)
		m_bDirtyTransform = m_bDirtyWorldMatrix = m_bDirtyWorldPosition = m_bDirtyAABBox = true;
	if (bDirtyScale)
		m_bDirtyTransform = m_bDirtyWorldMatrix = m_bDirtyWorldScale = m_bDirtyAABBox = true;
	if (bDirtyOrientation)
		m_bDirtyTransform = m_bDirtyWorldMatrix = m_bDirtyWorldOriention = m_bDirtyAABBox = true;

	m_pSceneNode->DirtyTransfrom(bDirtyPos, bDirtyScale, bDirtyOrientation);
}

Vector3 HrTransform::ConvertWorldToLocalDirection(const Vector3& worldDir)
{
	if (m_pSceneNode->GetParent())
	{
		const Quaternion& quaDerivedOrientation = GetParentOriention();
		return HrMath::TransformQuat(worldDir, HrMath::Inverse(quaDerivedOrientation));
	}
	else
	{
		return worldDir;
	}
}

const Vector3& HrTransform::GetParentScale()
{
	if (m_pSceneNode->GetParent())
		return m_pSceneNode->GetParent()->GetTransform()->GetWorldScale();
	else
		return m_s_v3One;
}

const Quaternion& HrTransform::GetParentOriention()
{
	if (m_pSceneNode->GetParent())
		return m_pSceneNode->GetParent()->GetTransform()->GetWorldOriention();
	else
		return m_s_quaIdentity;
}

const Vector3& HrTransform::GetParentPosition()
{
	if (m_pSceneNode->GetParent())
		return m_pSceneNode->GetParent()->GetTransform()->GetWorldPosition();
	else
		return m_s_v3Zero;
}

const Vector3 HrTransform::GetRotation()
{
	return m_vEulerAngles;
}

void HrTransform::SetAABBox(const AABBox& aabb)
{
	m_localAABBox = aabb;
	m_bDirtyAABBox = true;
}

const AABBox& HrTransform::GetLocalAABBox()
{
	return m_localAABBox;
}

const AABBox& HrTransform::GetWorldAABBox()
{
	if (m_bDirtyAABBox)
	{
		m_worldAABBox = HrMath::TransformAABB(m_localAABBox, GetWorldMatrix());
		m_bDirtyAABBox = false;
	}
	return m_worldAABBox;
}

