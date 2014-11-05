#pragma once

#include "HrCommon.h"

namespace HR
{
	class CHrBoundingBox
	{
	public:
		CHrBoundingBox();
		~CHrBoundingBox();

	public:
		bool               IsPointInside(D3DXVECTOR3& point);

	public:
		D3DXVECTOR3        m_vMin;
		D3DXVECTOR3        m_vMax;


	};


}

