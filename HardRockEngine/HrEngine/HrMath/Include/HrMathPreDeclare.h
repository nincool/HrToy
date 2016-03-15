#ifndef _HR_MATHPREDECLARE_H_
#define _HR_MATHPREDECLARE_H_


namespace Hr
{
	//选定基本类型
	class HrVector3;
	//typedef HrVector3 Vector3;
	class HrMatrix3;
	typedef HrMatrix3 Matrix3;
	class HrMatrix4;
	typedef HrMatrix4 Matrix4;
	
	template <typename T, int N>
	class Vector_T;
	typedef Hr::Vector_T<float, 2> Vector2;
	typedef Hr::Vector_T<float, 3> Vector3;
	typedef Hr::Vector_T<float, 4> Vector4;
	template <typename T>
	class Matrix4_T;
	//typedef Hr::Matrix4_T<float> Matrix4;



	typedef Vector3 float3;
	typedef Vector4 float4;
}

#endif


