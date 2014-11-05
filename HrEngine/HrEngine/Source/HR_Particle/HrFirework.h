#pragma once
#include "HrParticleSystem.h"

namespace HR
{
	class CHrFirework : public CHrParticleSystem
	{
	public:
		CHrFirework(D3DXVECTOR3* pOrigin, int nNumParticles);
		~CHrFirework();

	public:
		virtual void     ResetParticle(SParticleAttribute* pParticleAttribute);
		virtual void     Update(float fTimeDelta);
		virtual void     PreRender();
	};


}



