#include "HrMath.h"
#include <cassert>

using namespace HR;
CHrMath::CHrMath()
{
}


CHrMath::~CHrMath()
{
}

unsigned int CHrMath::GetURandomInt(uint nMin, uint nMax)
{
	if (nMax <= nMin)
	{
		return nMin;
	}

	uint iRandNum = rand();
	return iRandNum % (nMax - nMin) + nMin;
}

int CHrMath::GetRandomInt(int nMin, int nMax)
{
	if (nMax <= nMin)
	{
		return nMin;
	}

	int iRandNum = rand();
	return iRandNum % (nMax - nMin) + nMin;
}

float CHrMath::GetRandomFloat(float fMin, float fMax)
{
	if (fMin >= fMax)
	{
		return fMin;
	}

	float f = (rand() % 10000) * 0.0001f;

	return f * (fMax - fMin) + fMin;
}




void CHrMath::GetRandomVector(D3DXVECTOR3* pVOut, D3DXVECTOR3* pVMin, D3DXVECTOR3* pVMax)
{
	assert(pVOut && pVMin && pVMax && "Get Rand Vector Error! NULL pointer");

	pVOut->x = GetRandomFloat(pVMin->x, pVMax->x);
	pVOut->y = GetRandomFloat(pVMin->y, pVMax->y);
	pVOut->z = GetRandomFloat(pVMin->z, pVMax->z);
}

DWORD CHrMath::FloatToDword(float f)
{
	return *((DWORD*)&f);
}
