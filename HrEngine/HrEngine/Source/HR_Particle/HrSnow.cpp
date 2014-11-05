#include "HrSnow.h"
#include "../Hr_Math/HrMath.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

using namespace HR;
using namespace std;

CHrSnow::CHrSnow(CHrBoundingBox* pBoundingBox, int nNumParticles)
{
	//m_boundingBox = *pBoundingBox;
	m_pBoundingBox = pBoundingBox;
	//m_fSize = 0.25f;
	//m_dwVbNum = 2048;
	//m_dwVbOffset = 0;
	//m_dwVbBatchNum = 512;

	m_fSize = 1.25f;
	m_dwVbNum = 2;
	m_dwVbOffset = 0;
	m_dwVbBatchNum = 1;

	for (int i = 0; i < nNumParticles; ++i)
	{
		AddParticle();
	}
}

CHrSnow::~CHrSnow()
{

}

void CHrSnow::Update(float fTimeDelta)
{
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		iter->vPosition += iter->vVelocity * fTimeDelta;

		//is the point outside bounds?
		if (!m_pBoundingBox->IsPointInside(iter->vPosition))
		{
			ResetParticle(iter);
		}
	}
}

void CHrSnow::ResetParticle(SParticleAttribute* pParticleAttribute)
{
	pParticleAttribute->m_bIsAlive = true;

	CHrMath::GetRandomVector(&pParticleAttribute->vPosition, &m_pBoundingBox->m_vMin, &m_pBoundingBox->m_vMax);

	pParticleAttribute->vPosition.y = m_pBoundingBox->m_vMax.y;

	pParticleAttribute->vVelocity.x = CHrMath::GetRandomFloat(0.0f, 1.0f) * (-3.0f);
	pParticleAttribute->vVelocity.y = CHrMath::GetRandomFloat(0.0f, 1.0f) * (-10.0f);
	pParticleAttribute->vVelocity.z = 0.0f;

	pParticleAttribute->color = CHrD3DUtil::WHITE;
}

