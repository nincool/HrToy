#pragma once

#include "HrCommon.h"

namespace HR
{
	class CHrBoundingSphere
	{
	public:
		CHrBoundingSphere();
		~CHrBoundingSphere();

	public:
		D3DXVECTOR3 m_vCenter;
		float       m_fRadius;
	};


}
