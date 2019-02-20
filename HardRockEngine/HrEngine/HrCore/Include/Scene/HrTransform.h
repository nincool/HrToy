#ifndef _HR_TRANSFROM_H_
#define _HR_TRANSFROM_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrTransform
	{
	public:
		enum EnumTransformSpace
		{
			TS_LOCAL,
			TS_PARENT,
			TS_WORLD
		};

	public:
		HrTransform(HrSceneNode* pSceneNode);

		void UpdateTransform(float fDelta);

		void SetPosition(const Vector3& v3Pos);
		void SetPosition(REAL x, REAL y, REAL z);
		const Vector3& GetPosition();

		void SetOrientation(const Quaternion& orientation);
		const Quaternion& GetOrientation() const;
		void SetRotation(const Vector3& angle);
		const Vector3 GetRotation();

		const Vector3& GetForward() const;
		const Vector3& GetRight() const;
		const Vector3& GetUp() const;
		const Vector3& GetWorldForward();
		const Vector3& GetWorldRight();
		const Vector3& GetWorldUp();

		void SetScale(const Vector3& v3Scale);
		const Vector3& GetScale();

		/**
		 @Comment: ת��λ�� [10/29/2018 By Hr]
		 @Param: TS_LOCAL  ����������ϵΪ��׼ �����ƶ�z���൱��Forward
				  TS_PARENT �Ը��ڵ�����ϵΪ��׼ ���͸ı�Unity��������xyzһ��
				  TS_WORLD  ����������ϵΪ��׼ ����Unity��Globalһ��
		*/
		void Translate(const Vector3& v3, EnumTransformSpace relativeTo = TS_PARENT);

		const Vector3& GetWorldScale();
		const Quaternion& GetWorldOriention();
		const Vector3& GetWorldPosition();
		const Matrix4& GetWorldMatrix();

		void Rotate(const Vector3& angle, EnumTransformSpace relativeTo = TS_LOCAL);
		void Rotate(const Quaternion& q, EnumTransformSpace relativeTo = TS_LOCAL);

		void SetAABBox(const AABBox& aabb);
		const AABBox& GetLocalAABBox();
		const AABBox& GetWorldAABBox();

		bool GetTransformDirty();
		void SetTransformDirty(bool bDirty);

		void DirtyTransform(bool bDirtyPos = false, bool bDirtyScale = false, bool bDirtyOrientation = false);

	protected:
		Vector3 ConvertWorldToLocalDirection(const Vector3& worldDir);

		const Vector3& GetParentScale();
		const Quaternion& GetParentOriention();
		const Vector3& GetParentPosition();

		void DecomposeLocalOriention(const Quaternion& orientation);
		void DecomposeWorldOriention(const Quaternion& orientation);
	protected:
		HrSceneNode* m_pSceneNode;

		Vector3 m_vPosition;
		Vector3 m_vForward;
		Vector3 m_vRight;
		Vector3 m_vUp;
		Vector3 m_vScale;
		Vector3 m_vEulerAngles;
		Quaternion m_orientation;

		Matrix4 m_matLocalWorldMatrix;
		
		bool m_bDirtyWorldMatrix;
		Matrix4 m_matWorldMatrix;

		bool m_bDirtyWorldScale;
		Vector3 m_vWorldScale;
		bool m_bDirtyWorldOriention;
		Quaternion m_worldOriention;
		Vector3 m_vWorldForward;
		Vector3 m_vWorldRight;
		Vector3 m_vWorldUp;
		bool m_bDirtyWorldPosition;
		Vector3 m_vWorldPosition;

		bool m_bDirtyTransform;

		static Quaternion m_s_quaIdentity;
		static Vector3 m_s_v3Zero;
		static Vector3 m_s_v3One;

		bool m_bDirtyAABBox;
		AABBox m_localAABBox;
		AABBox m_worldAABBox;
	};
}


#endif



