#include "HrFirework.h"
#include "../Hr_Math/HrMath.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

using namespace HR;
CHrFirework::CHrFirework(D3DXVECTOR3* pOrigin, int nNumParticles)
{
	m_vOrigin = *pOrigin;

	m_fSize = 3.9f;
	m_dwVbNum = 2048;
	m_dwVbOffset = 0;
	m_dwVbBatchNum = 512;

	for (int i = 0; i < nNumParticles; ++i)
	{
		AddParticle();
	}
}

CHrFirework::~CHrFirework()
{
}

void CHrFirework::ResetParticle(SParticleAttribute* pParticleAttribute)
{
	pParticleAttribute->m_bIsAlive = true;
	pParticleAttribute->vPosition = m_vOrigin;
	
	D3DXVECTOR3 vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	CHrMath::GetRandomVector(&pParticleAttribute->vVelocity, &vMin, &vMax);

	D3DXVec3Normalize(&pParticleAttribute->vVelocity, &pParticleAttribute->vVelocity);

	pParticleAttribute->vVelocity *= 100.0f;

	pParticleAttribute->color = D3DXCOLOR(CHrMath::GetRandomFloat(0.0f, 1.0f)
		, CHrMath::GetRandomFloat(0.0f, 1.0f)
		, CHrMath::GetRandomFloat(0.0f, 1.0f)
		, 1.0f);
	pParticleAttribute->m_fAge = 0.0f;
	// lives for 2 seconds
	pParticleAttribute->m_fLifeTime = 2.0f;
}

void CHrFirework::Update(float fTimeDelta)
{
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		if (iter->m_bIsAlive)
		{
			iter->vPosition += iter->vVelocity * fTimeDelta;
			iter->m_fAge += fTimeDelta;

			if (iter->m_fAge > iter->m_fLifeTime)
			{
				iter->m_bIsAlive = false;
			}
		}
	}
}

void CHrFirework::PreRender()
{
	CHrParticleSystem::PreRender();

	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}







