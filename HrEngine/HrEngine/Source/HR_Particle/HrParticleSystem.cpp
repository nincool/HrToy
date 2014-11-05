#include "HrParticleSystem.h"
#include "HrCommon.h"
#include "../Hr_Math/HrMath.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>

using namespace HR;
CHrParticleSystem::CHrParticleSystem()
{
	m_pD3DDevice = NULL;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;

	m_dwVbNum = 0;
}

CHrParticleSystem::~CHrParticleSystem()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);

	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		SAFE_DELETE(iter);
	}
	m_lisParticles.clear();
}

bool CHrParticleSystem::Initialize(IDirect3DDevice9* pDevice, const char* pTextureFileName)
{
	m_pD3DDevice = pDevice;

	HRESULT hr;

	hr = m_pD3DDevice->CreateVertexBuffer(m_dwVbNum * sizeof(SParticle)
		, D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY
		, SParticle::PARTICLE_FVF
		, D3DPOOL_DEFAULT
		, &m_pVertexBuffer
		, NULL);

	if (FAILED(hr))
	{
		return false;
	}

	hr = D3DXCreateTextureFromFile(m_pD3DDevice, pTextureFileName, &m_pTexture);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void CHrParticleSystem::Reset()
{
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		ResetParticle(iter);
	}
}

void CHrParticleSystem::AddParticle()
{
	SParticleAttribute* pParticleAttr = new SParticleAttribute();
	ResetParticle(pParticleAttr);

	m_lisParticles.push_back(pParticleAttr);
}

void CHrParticleSystem::PreRender()
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, CHrMath::FloatToDword(m_fSize));

	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, CHrMath::FloatToDword(0.0f));
	
	// FinalSize = ViewportHeight * Size * squr(1/(A + B(D) + C(D*D)))
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, CHrMath::FloatToDword(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, CHrMath::FloatToDword(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, CHrMath::FloatToDword(1.0f));

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CHrParticleSystem::Render()
{
	// The render method works by filling a section of the vertex buffer with data, then we render that section.  
	// While that section is rendering we lock a new section and begin to fill that section.  
	// Once that sections filled we render it. This process continues until all the particles have been drawn.  
	// The benifit of this method is that we keep the video card and the CPU busy.  
	if (m_lisParticles.empty())
	{
		return;
	}
	// set render states
	PreRender();

	m_pD3DDevice->SetTexture(0, m_pTexture);
	m_pD3DDevice->SetFVF(SParticle::PARTICLE_FVF);
	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SParticle));

	//
	// render batches one by one
	//

	// start at beginning if we're at the end of the vertex buffer
	if (m_dwVbOffset >= m_dwVbNum)
	{
		m_dwVbOffset = 0;
	}

	SParticle* pParticle;

	m_pVertexBuffer->Lock(m_dwVbOffset * sizeof(SParticle)
		, m_dwVbBatchNum * sizeof(SParticle)
		, (void**)&pParticle
		, m_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD dwNumParticleInBatch = 0;

	// until all particles have been rendered
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		if (!iter->m_bIsAlive)
		{
			continue;
		}

		// copy a batch of the living particles to the next vertex buffer segment
		pParticle->vPosition = iter->vPosition;
		pParticle->color = (D3DCOLOR)iter->color;
		// next element
		++pParticle;

		++dwNumParticleInBatch;

		// if this batch full?
		if (dwNumParticleInBatch == m_dwVbBatchNum)
		{
			m_pVertexBuffer->Unlock();
			m_pD3DDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVbOffset, m_dwVbBatchNum);

			m_dwVbOffset += m_dwVbBatchNum;

			if (m_dwVbOffset >= m_dwVbNum)
			{
				m_dwVbOffset = 0;
			}

			m_pVertexBuffer->Lock(m_dwVbOffset * sizeof(SParticle)
				, m_dwVbBatchNum * sizeof(SParticle)
				, (void**)&pParticle
				, m_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

			dwNumParticleInBatch = 0;
		}
	}

	m_pVertexBuffer->Unlock();

	// Its possible that the LAST batch being filled never got rendered because the condition 
	// (num_particles_in_batch == m_vb_batch_num) would not have been satisfied.  
	// We draw the last partially filled batch now.	
	if (dwNumParticleInBatch)
	{
		m_pD3DDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwVbOffset, dwNumParticleInBatch);
	}
	// next block
	m_dwVbOffset += m_dwVbBatchNum;

	PostRender();
}

void CHrParticleSystem::PostRender()
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}


bool CHrParticleSystem::IsEmpty()
{
	return m_lisParticles.empty();
}

bool CHrParticleSystem::IsDead()
{
	BOOST_FOREACH(BOOST_TYPEOF(*m_lisParticles.begin())& iter, m_lisParticles)
	{
		if (iter->m_bIsAlive)
		{
			return false;
		}
	}

	return true;
}

void CHrParticleSystem::RemoveDeadParticles()
{
	std::list<SParticleAttribute*>::iterator iter = m_lisParticles.begin();

	while (iter != m_lisParticles.end())
	{
		if (!(*iter)->m_bIsAlive)
		{
			iter = m_lisParticles.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
