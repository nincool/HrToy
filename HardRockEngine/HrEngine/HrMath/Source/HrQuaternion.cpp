#include "HrQuaternion.h"
#include "HrMathCom.h"
#include "HrAngle.h"

using namespace Hr;

const REAL HrQuaternion::msEpsilon = 1e-03;
const HrQuaternion HrQuaternion::ZERO(0, 0, 0, 0);
const HrQuaternion HrQuaternion::IDENTITY(1, 0, 0, 0);

void HrQuaternion::FromRotationMatrix(const Matrix3& kRot)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".

	REAL fTrace = kRot[0][0] + kRot[1][1] + kRot[2][2];
	REAL fRoot;

	if (fTrace > 0.0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = HrMath::Sqrt(fTrace + 1.0f);  // 2w
		m_w = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;  // 1/(4w)
		m_x = (kRot[2][1] - kRot[1][2])*fRoot;
		m_y = (kRot[0][2] - kRot[2][0])*fRoot;
		m_z = (kRot[1][0] - kRot[0][1])*fRoot;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if (kRot[1][1] > kRot[0][0])
			i = 1;
		if (kRot[2][2] > kRot[i][i])
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		fRoot = HrMath::Sqrt(kRot[i][i] - kRot[j][j] - kRot[k][k] + 1.0f);
		REAL* apkQuat[3] = { &m_x, &m_y, &m_z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;
		m_w = (kRot[k][j] - kRot[j][k])*fRoot;
		*apkQuat[j] = (kRot[j][i] + kRot[i][j])*fRoot;
		*apkQuat[k] = (kRot[k][i] + kRot[i][k])*fRoot;
	}
}

void HrQuaternion::FromAngleAxis(const Radian& rfAngle, const Vector3& rkAxis)
{
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	Radian fHalfAngle(rfAngle * 0.5f);
	REAL fSin = HrMath::Sin(fHalfAngle.valueRadians());
	m_w = HrMath::Cos(fHalfAngle.valueRadians());
	m_x = fSin*rkAxis.x();
	m_y = fSin*rkAxis.y();
	m_z = fSin*rkAxis.z();

}

void HrQuaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	Matrix3 kRot;

	kRot[0][0] = xAxis.x();
	kRot[1][0] = xAxis.y();
	kRot[2][0] = xAxis.z();

	kRot[0][1] = yAxis.x();
	kRot[1][1] = yAxis.y();
	kRot[2][1] = yAxis.z();

	kRot[0][2] = zAxis.x();
	kRot[1][2] = zAxis.y();
	kRot[2][2] = zAxis.z();

	FromRotationMatrix(kRot);

}

void HrQuaternion::FromAxes(const Vector3* akAxis)
{
	Matrix3 kRot;

	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		kRot[0][iCol] = akAxis[iCol].x();
		kRot[1][iCol] = akAxis[iCol].y();
		kRot[2][iCol] = akAxis[iCol].z();
	}

	FromRotationMatrix(kRot);
}

void HrQuaternion::ToRotationMatrix(Matrix3& kRot) const
{
	REAL fTx = m_x + m_x;
	REAL fTy = m_y + m_y;
	REAL fTz = m_z + m_z;
	REAL fTwx = fTx*m_w;
	REAL fTwy = fTy*m_w;
	REAL fTwz = fTz*m_w;
	REAL fTxx = fTx*m_x;
	REAL fTxy = fTy*m_x;
	REAL fTxz = fTz*m_x;
	REAL fTyy = fTy*m_y;
	REAL fTyz = fTz*m_y;
	REAL fTzz = fTz*m_z;

	kRot[0][0] = 1.0f - (fTyy + fTzz);
	kRot[0][1] = fTxy - fTwz;
	kRot[0][2] = fTxz + fTwy;
	kRot[1][0] = fTxy + fTwz;
	kRot[1][1] = 1.0f - (fTxx + fTzz);
	kRot[1][2] = fTyz - fTwx;
	kRot[2][0] = fTxz - fTwy;
	kRot[2][1] = fTyz + fTwx;
	kRot[2][2] = 1.0f - (fTxx + fTyy);

}

void HrQuaternion::ToAngleAxis(Radian& rfAngle, Vector3& rkAxis) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	REAL fSqrLength = m_x*m_x + m_y*m_y + m_z*m_z;
	if (fSqrLength > 0.0)
	{
		rfAngle = 2.0f*HrMath::Acos(m_w);
		REAL fInvLength = HrMath::Recip_Sqrt(fSqrLength);
		rkAxis.x(m_x*fInvLength);
		rkAxis.y(m_y*fInvLength);
		rkAxis.z(m_z*fInvLength);
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		rfAngle = Radian(0.0);
		rkAxis.x(1.0f);
		rkAxis.y(0.0f);
		rkAxis.z(0.0f);
	}

}

void HrQuaternion::ToAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const
{
	Matrix3 kRot;

	ToRotationMatrix(kRot);

	xAxis.x(kRot[0][0]);
	xAxis.y(kRot[1][0]);
	xAxis.z(kRot[2][0]);

	yAxis.x(kRot[0][1]);
	yAxis.y(kRot[1][1]);
	yAxis.z(kRot[2][1]);

	zAxis.x(kRot[0][2]);
	zAxis.y(kRot[1][2]);
	zAxis.z(kRot[2][2]);

}

Vector3 HrQuaternion::xAxis(void) const
{
	//Real fTx  = 2.0*x;
	REAL fTy = 2.0f*m_y;
	REAL fTz = 2.0f*m_z;
	REAL fTwy = fTy*m_w;
	REAL fTwz = fTz*m_w;
	REAL fTxy = fTy*m_x;
	REAL fTxz = fTz*m_x;
	REAL fTyy = fTy*m_y;
	REAL fTzz = fTz*m_z;

	return Vector3(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
}
//-----------------------------------------------------------------------
Vector3 HrQuaternion::yAxis(void) const
{
	REAL fTx = 2.0f*m_x;
	REAL fTy = 2.0f*m_y;
	REAL fTz = 2.0f*m_z;
	REAL fTwx = fTx*m_w;
	REAL fTwz = fTz*m_w;
	REAL fTxx = fTx*m_x;
	REAL fTxy = fTy*m_x;
	REAL fTyz = fTz*m_y;
	REAL fTzz = fTz*m_z;

	return Vector3(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
}
//-----------------------------------------------------------------------
Vector3 HrQuaternion::zAxis(void) const
{
	REAL fTx = 2.0f*m_x;
	REAL fTy = 2.0f*m_y;
	REAL fTz = 2.0f*m_z;
	REAL fTwx = fTx*m_w;
	REAL fTwy = fTy*m_w;
	REAL fTxx = fTx*m_x;
	REAL fTxz = fTz*m_x;
	REAL fTyy = fTy*m_y;
	REAL fTyz = fTz*m_y;

	return Vector3(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
}

//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::operator+ (const HrQuaternion& rkQ) const
{
	return HrQuaternion(m_w + rkQ.m_w, m_x + rkQ.m_x, m_y + rkQ.m_y, m_z + rkQ.m_z);
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::operator- (const HrQuaternion& rkQ) const
{
	return HrQuaternion(m_w - rkQ.m_w, m_x - rkQ.m_x, m_y - rkQ.m_y, m_z - rkQ.m_z);
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::operator* (const HrQuaternion& rkQ) const
{
	// NOTE:  Multiplication is not generally commutative, so in most
	// cases p*q != q*p.

	return HrQuaternion
	(
		m_w * rkQ.m_w - m_x * rkQ.m_x - m_y * rkQ.m_y - m_z * rkQ.m_z,
		m_w * rkQ.m_x + m_x * rkQ.m_w + m_y * rkQ.m_z - m_z * rkQ.m_y,
		m_w * rkQ.m_y + m_y * rkQ.m_w + m_z * rkQ.m_x - m_x * rkQ.m_z,
		m_w * rkQ.m_z + m_z * rkQ.m_w + m_x * rkQ.m_y - m_y * rkQ.m_x
	);
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::operator* (REAL fScalar) const
{
	return HrQuaternion(fScalar*m_w, fScalar*m_x, fScalar*m_y, fScalar*m_z);
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::operator- () const
{
	return HrQuaternion(-m_w, -m_x, -m_y, -m_z);
}
//-----------------------------------------------------------------------
REAL HrQuaternion::Dot(const HrQuaternion& rkQ) const
{
	return m_w*rkQ.m_w + m_x*rkQ.m_x + m_y*rkQ.m_y + m_z*rkQ.m_z;
}
//-----------------------------------------------------------------------
REAL HrQuaternion::Norm() const
{
	return m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z;
}

REAL HrQuaternion::Normalise(void)
{
	REAL len = Norm();
	REAL factor = 1.0f / HrMath::Sqrt(len);
	*this = *this * factor;
	return len;

}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::Inverse() const
{
	REAL fNorm = m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z;
	if (fNorm > 0.0)
	{
		REAL fInvNorm = 1.0f / fNorm;
		return HrQuaternion(m_w*fInvNorm, -m_x*fInvNorm, -m_y*fInvNorm, -m_z*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		return ZERO;
	}
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::UnitInverse() const
{
	// assert:  'this' is unit length
	return HrQuaternion(m_w, -m_x, -m_y, -m_z);
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::Exp() const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	Radian fAngle(HrMath::Sqrt(m_x*m_x + m_y*m_y + m_z*m_z));
	REAL fSin = HrMath::Sin(fAngle.valueRadians());

	HrQuaternion kResult;
	kResult.m_w = HrMath::Cos(fAngle.valueRadians());

	if (HrMath::Abs(fSin) >= msEpsilon)
	{
		REAL fCoeff = fSin / (fAngle.valueRadians());
		kResult.m_x = fCoeff*m_x;
		kResult.m_y = fCoeff*m_y;
		kResult.m_z = fCoeff*m_z;
	}
	else
	{
		kResult.m_x = m_x;
		kResult.m_y = m_y;
		kResult.m_z = m_z;
	}

	return kResult;
}
//-----------------------------------------------------------------------
HrQuaternion HrQuaternion::Log() const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	HrQuaternion kResult;
	kResult.m_w = 0.0;

	if (HrMath::Abs(m_w) < 1.0)
	{
		Radian fAngle(HrMath::Acos(m_w));
		REAL fSin = HrMath::Sin(fAngle.valueRadians());
		if (HrMath::Abs(fSin) >= msEpsilon)
		{
			REAL fCoeff = fAngle.valueRadians() / fSin;
			kResult.m_x = fCoeff*m_x;
			kResult.m_y = fCoeff*m_y;
			kResult.m_z = fCoeff*m_z;
			return kResult;
		}
	}

	kResult.m_x = m_x;
	kResult.m_y = m_y;
	kResult.m_z = m_z;

	return kResult;
}
//-----------------------------------------------------------------------
//Vector3 HrQuaternion::operator* (const Vector3& v) const
//{
//	// nVidia SDK implementation
//	Vector3 uv, uuv;
//	Vector3 qvec(x, y, z);
//	uv = qvec.crossProduct(v);
//	uuv = qvec.crossProduct(uv);
//	uv *= (2.0f * w);
//	uuv *= 2.0f;
//
//	return v + uv + uuv;
//
//}

