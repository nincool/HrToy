#pragma once

#include "HrParticleSystem.h"

namespace HR
{
	class CHrBoundingBox;
	class CHrSnow : public CHrParticleSystem
	{
	public:
		CHrSnow(CHrBoundingBox* pBoundingBox, int nNumParticles);
		~CHrSnow();

	public:
		virtual void            Update(float fTimeDelta);
		virtual void            ResetParticle(SParticleAttribute* pParticleAttribute);
	};

}

