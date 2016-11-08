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

		void SetPosition(const Vector3& v3Pos);
		void SetPosition(REAL x, REAL y, REAL z);
		const Vector3& GetPosition();

		void SetLocalPosition(const Vector3& v3Pos);
		void SetLocalPosition(REAL x, REAL y, REAL z);
		const Vector3& GetLocalPosition();

		virtual void Translate(const Vector3& v3);

		/*
		@brief	Rotate the node around the z-axis [11/1/2016 By Hr]
		*/
		void Roll(const Radian& angle, EnumTransformSpace relative = TS_LOCAL);
		/*
		@brief	Rotate the node around the z-axis [11/1/2016 By Hr]
		*/
		void Pitch(const Radian& angle, EnumTransformSpace relative = TS_LOCAL);
		/*
		@brief	Rotate the node around the z-axis [11/1/2016 By Hr]
		*/
		void Yaw(const Radian& angle, EnumTransformSpace relative = TS_LOCAL);

		void Rotate(const Vector3& axis, const Radian& angle, EnumTransformSpace relativeTo = TS_LOCAL);

		void Rotate(const Quaternion& q, EnumTransformSpace relativeTo = TS_LOCAL);
	protected:
		HR_SYNTHESIZE(Vector3, m_vWordPosition, WordPosition);
		HR_SYNTHESIZE(Vector3, m_vLocalPosition, LocalPosition);
		HR_SYNTHESIZE(Vector3, m_vForward, Forward);
		HR_SYNTHESIZE(Vector3, m_vRight, Right);
		HR_SYNTHESIZE(Vector3, m_vUp, Up);
		HR_SYNTHESIZE(Vector3, m_vEulerAngles, EulerAngles);
		HR_SYNTHESIZE(Vector3, m_vLocalEulerAngles, LocalEulerAngles);
		HR_SYNTHESIZE(Quaternion, m_quaRotation, Rotation);
		HR_SYNTHESIZE(Matrix4, m_matLocalWorldMatrix, LocalWorldMatrix);

		HR_SYNTHESIZE(HrSceneNode*, m_pSceneNode, SceneNode);

	};
}


#endif



