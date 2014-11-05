#pragma once
#include "HrParticleSystem.h"

namespace HR
{
	class CHrCamera;

	class CHrParticleGun : public CHrParticleSystem
	{
	public:
		CHrParticleGun(CHrCamera* pCamera);
		~CHrParticleGun();

	public:
		virtual void ResetParticle(SParticleAttribute* pParticleAttribute);
		
		virtual void Update(float fTimeDelta);

	private:
		CHrCamera*     m_pCamera;
	};


}



