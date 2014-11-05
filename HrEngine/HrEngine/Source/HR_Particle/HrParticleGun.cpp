#include "HrParticleGun.h"
#include "../HR_Camera/HrCamera.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

using namespace HR;

CHrParticleGun::CHrParticleGun(CHrCamera* pCamera)
{
	m_pCamera = pCamera;

	m_fSize = 0.8f;
	m_dwVbNum = 2048;
	m_dwVbOffset = 0;
	m_dwVbBatchNum = 512;
}

CHrParticleGun::~CHrParticleGun()
{

}

void CHrParticleGun::ResetParticle(SParticleAttribute* pParticleAttribute)
{
	pParticleAttribute->m_bIsAlive = true;
	
	D3DXVECTOR3 v3CameraDir;
	m_pCamera->GetLookDir(v3CameraDir);

	// change to camera position
	m_pCamera->GetCameraPosition(pParticleAttribute->vPosition);
	// sightly below camera so it looks like we're carrying a gun
	pParticleAttribute->vPosition.y -= 1.0f;

	// travels in the direction the camera is looking
	pParticleAttribute->vVelocity = v3CameraDir * 10.0f;

	// green
	pParticleAttribute->color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pParticleAttribute->m_fAge = 0.0f;
	// lives for 1 seconds
	pParticleAttribute->m_fLifeTime = 1.0f;

}

void CHrParticleGun::Update(float fTimeDelta)
{
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		iter->vPosition += iter->vVelocity * fTimeDelta;
		iter->m_fAge += fTimeDelta;

		if (iter->m_fAge > iter->m_fLifeTime)
		{
			// Kill
			iter->m_bIsAlive = false;
		}
	}

	RemoveDeadParticles();
}

