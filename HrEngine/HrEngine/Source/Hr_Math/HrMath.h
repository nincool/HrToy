#pragma once

#include "HrCommon.h"

namespace HR
{
	class CHrMath
	{
	public:
		CHrMath();
		~CHrMath();

	public:
		static uint          GetURandomInt(uint nMin, uint nMax);
		static int           GetRandomInt(int nMin, int nMax);
		static float         GetRandomFloat(float fMin, float fMax);


		static void          GetRandomVector(D3DXVECTOR3* pVOut, D3DXVECTOR3* pVMin, D3DXVECTOR3* pVMax);

		static DWORD         FloatToDword(float f);
	};

}
