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
		HrTransform(const std::function<void (bool, bool, bool)>& funDirtyTrans);

		void SetParentTransform(const HrTransformPtr& pTrans);

		void UpdateTransform(float fDelta);

		void SetPosition(const Vector3& v3Pos);
		void SetPosition(REAL x, REAL y, REAL z);
		const Vector3& GetPosition();

		void SetOrientation(const Quaternion& orientation);
		const Quaternion& GetOrientation() const;
		void SetRotation(const Vector3& angle);

		const Vector3& GetForward() const;
		const Vector3& GetRight() const;
		const Vector3& GetUp() const;

		void SetScale(const Vector3& v3Scale);
		const Vector3& GetScale();

		void Translate(const Vector3& v3, EnumTransformSpace relativeTo = TS_LOCAL);

		const Vector3& GetWorldScale();
		const Quaternion& GetWorldOriention();
		const Vector3& GetWorldPosition();

		const Matrix4& GetWorldMatrix();
	
		/*
		@brief	Rotate the node around the z-axis [11/1/2016 By Hr]
		*/
		void Roll(const Radian& angle, EnumTransformSpace relativeTo = TS_LOCAL);
		/*
		@brief	Rotate the node around the x-axis [11/1/2016 By Hr]
		*/
		void Pitch(const Radian& angle, EnumTransformSpace relativeTo = TS_LOCAL);
		/*
		@brief	Rotate the node around the y-axis [11/1/2016 By Hr]
		*/
		void Yaw(const Radian& angle, EnumTransformSpace relativeTo = TS_LOCAL);

		void Rotate(const Vector3& axis, const Radian& angle, EnumTransformSpace relativeTo = TS_LOCAL);

		void Rotate(const Vector3& angle, EnumTransformSpace relativeTo = TS_LOCAL);

		void Rotate(const Quaternion& q, EnumTransformSpace relativeTo = TS_LOCAL);

		bool GetTransformDirty();
		void SetTransformDirty(bool bDirty);

		void DirtyTransform(bool bDirtyPos = false, bool bDirtyScale = false, bool bDirtyOrientation = false);
	protected:
		void UpdateFromParent();
	protected:
		HrTransformPtr m_pParentTransform;

		Vector3 m_vPosition;
		Vector3 m_vForward;
		Vector3 m_vRight;
		Vector3 m_vUp;
		Vector3 m_vScale;
		Vector3 m_vEulerAngles;
		Vector3 m_vLocalEulerAngles;
		Quaternion m_orientation;

		Matrix4 m_matLocalWorldMatrix;
		
		bool m_bDirtyWorldMatrix;
		Matrix4 m_matWorldMatrix;

		bool m_bDirtyWorldScale;
		Vector3 m_vWorldScale;
		bool m_bDirtyWorldOriention;
		Quaternion m_worldOriention;
		bool m_bDirtyWorldPosition;
		Vector3 m_vWorldPosition;

		bool m_bDirtyTransform;

		std::function<void(bool, bool, bool)> m_funDirtyTrans;
	};
}


#endif



