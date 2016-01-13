#include "HrMatrix3.h"
#include "HrMath.h"

using namespace Hr;

const HrMatrix3 HrMatrix3::ZERO(0, 0, 0, 0, 0, 0, 0, 0, 0);
const HrMatrix3 HrMatrix3::IDENTITY(1, 0, 0, 0, 1, 0, 0, 0, 1);

HrVector3 HrMatrix3::GetColumn(size_t nCol) const
{
	assert(nCol < 3);
	return HrVector3(m[0][nCol], m[1][nCol], m[2][nCol]);
}

void HrMatrix3::SetColumn(size_t nCol, const HrVector3& v3)
{
	assert(nCol < 3);
	m[0][nCol] = v3.x;
	m[1][nCol] = v3.y;
	m[2][nCol] = v3.z;
}

void HrMatrix3::FromAxes(const HrVector3& xAxis, const HrVector3& yAxis, const HrVector3& zAxis)
{
	SetColumn(0, xAxis);
	SetColumn(1, yAxis);
	SetColumn(2, zAxis);
}

bool HrMatrix3::operator==(const HrMatrix3& rkMatrix) const
{
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			if (m[nRow][nCol] != rkMatrix.m[nRow][nCol])
			{
				return false;
			}
		}
	}
	return true;
}

HrMatrix3 HrMatrix3::operator+(const HrMatrix3& rkMatrix) const
{
	HrMatrix3 kSum;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kSum.m[nRow][nCol] = m[nRow][nCol] + rkMatrix.m[nRow][nCol];
		}
	}

	return kSum;
}

HrMatrix3 HrMatrix3::operator-(const HrMatrix3& rkMatrix) const
{
	HrMatrix3 kDiff;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kDiff.m[nRow][nCol] = m[nRow][nCol] - rkMatrix.m[nRow][nCol];
		}
	}

	return kDiff;
}

HrMatrix3 HrMatrix3::operator*(const HrMatrix3& rkMatrix) const
{
	HrMatrix3 kProd;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kProd.m[nRow][nCol] = m[nRow][0] * rkMatrix.m[0][nCol] + m[nRow][1] * rkMatrix.m[1][nCol] + m[nRow][2] * rkMatrix.m[2][nCol];
		}
	}
	return kProd;
}

Hr::HrMatrix3 Hr::HrMatrix3::operator-() const
{
	HrMatrix3 kNeg;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kNeg[nRow][nCol] = -m[nRow][nCol];
		}
	}
	return kNeg;
}

HrVector3 HrMatrix3::operator*(const HrVector3& rkPoint) const
{
	HrVector3 kProd;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		kProd[nRow] = rkPoint[0] * m[nRow][0] + rkPoint[1] * m[nRow][1] + rkPoint[2] * m[nRow][2];
	}

	return kProd;
}

Hr::HrMatrix3 Hr::HrMatrix3::operator*(REAL fScalar) const
{
	HrMatrix3 kProd;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kProd[nRow][nCol] = fScalar * m[nRow][nCol];
		}
	}

	return kProd;
}

Hr::HrMatrix3 Hr::HrMatrix3::Transpose() const
{
	HrMatrix3 kTranspose;
	for (size_t nRow = 0; nRow < 3; ++nRow)
	{
		for (size_t nCol = 0; nCol < 3; ++nCol)
		{
			kTranspose[nRow][nCol] = m[nCol][nRow];
		}
	}

	return kTranspose;
}

bool HrMatrix3::Inverse(HrMatrix3& rkInverse, REAL fTolerance /*= 1e-06*/) const
{
	// Invert a 3x3 using cofactors.  This is about 8 times faster than
	// the Numerical Recipes code which uses Gaussian elimination.
	//TT!

	rkInverse[0][0] = m[1][1] * m[2][2] -
		m[1][2] * m[2][1];
	rkInverse[0][1] = m[0][2] * m[2][1] -
		m[0][1] * m[2][2];
	rkInverse[0][2] = m[0][1] * m[1][2] -
		m[0][2] * m[1][1];
	rkInverse[1][0] = m[1][2] * m[2][0] -
		m[1][0] * m[2][2];
	rkInverse[1][1] = m[0][0] * m[2][2] -
		m[0][2] * m[2][0];
	rkInverse[1][2] = m[0][2] * m[1][0] -
		m[0][0] * m[1][2];
	rkInverse[2][0] = m[1][0] * m[2][1] -
		m[1][1] * m[2][0];
	rkInverse[2][1] = m[0][1] * m[2][0] -
		m[0][0] * m[2][1];
	rkInverse[2][2] = m[0][0] * m[1][1] -
		m[0][1] * m[1][0];

	REAL fDet =
		m[0][0] * rkInverse[0][0] +
		m[0][1] * rkInverse[1][0] +
		m[0][2] * rkInverse[2][0];

	if (HrMath::Abs(fDet) <= fTolerance)
		return false;

	REAL fInvDet = 1.0f / fDet;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			rkInverse[iRow][iCol] *= fInvDet;
	}

	return true;
}

HrMatrix3 HrMatrix3::Inverse(REAL fTolerance /*= 1e-06*/) const
{
	HrMatrix3 kInverse = HrMatrix3::ZERO;
	Inverse(kInverse, fTolerance);
	return kInverse;
}

REAL HrMatrix3::Determinant() const
{
	REAL fCofactor00 = m[1][1] * m[2][2] -
		m[1][2] * m[2][1];
	REAL fCofactor10 = m[1][2] * m[2][0] -
		m[1][0] * m[2][2];
	REAL fCofactor20 = m[1][0] * m[2][1] -
		m[1][1] * m[2][0];

	REAL fDet =
		m[0][0] * fCofactor00 +
		m[0][1] * fCofactor10 +
		m[0][2] * fCofactor20;

	return fDet;
}





