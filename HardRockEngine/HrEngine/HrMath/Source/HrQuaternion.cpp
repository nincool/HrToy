#include "HrQuaternion.h"
#include "HrMathCom.h"

using namespace Hr;

void HrQuaternion::FromAxes(const HrVector3* akAxis)
{
	HrMatrix3 kRot;
	
	for (size_t nCol = 0; nCol < 3; ++nCol)
	{
		kRot[0][nCol] = akAxis[nCol].x();
		kRot[1][nCol] = akAxis[nCol].y();
		kRot[2][nCol] = akAxis[nCol].z();
	}
}

void HrQuaternion::FromRotationMatrix(const HrMatrix3& kRot)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".

	REAL fTrace = kRot[0][0] + kRot[1][1] + kRot[2][2];
	REAL fRoot;

	if (fTrace > 0.0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = HrMath::Sqrt(fTrace + 1.0f);  // 2w
		w = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;  // 1/(4w)
		x = (kRot[2][1] - kRot[1][2])*fRoot;
		y = (kRot[0][2] - kRot[2][0])*fRoot;
		z = (kRot[1][0] - kRot[0][1])*fRoot;
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
		REAL* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;
		w = (kRot[k][j] - kRot[j][k])*fRoot;
		*apkQuat[j] = (kRot[j][i] + kRot[i][j])*fRoot;
		*apkQuat[k] = (kRot[k][i] + kRot[i][k])*fRoot;
	}
}


