#pragma once

#include "HrCommon.h"
#include "../HR_Physics/HrBoundingBox.h"

#include <list>

namespace HR
{
	struct SParticle
	{
		D3DXVECTOR3 vPosition;
		D3DCOLOR color;

		const static DWORD PARTICLE_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};


	struct SParticleAttribute
	{
		SParticleAttribute()
		{
		}

		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vVelocity;
		D3DXVECTOR3 vAcceleration;

		//生命时间
		float       m_fLifeTime;
		//存活了多久
		float       m_fAge;

		D3DXCOLOR   color;
		D3DXCOLOR   colorFade;
		bool        m_bIsAlive;
	};

	class CHrParticleSystem
	{
	public:
		CHrParticleSystem();
		virtual ~CHrParticleSystem();

	public:
		virtual bool       Initialize(IDirect3DDevice9* pDevice, const char* pTextureFileName);

		virtual void       Reset();

		virtual void       ResetParticle(SParticleAttribute* pParticleAttribute) = 0;
		virtual void       AddParticle();

		virtual void       Update(float fTimeDelta) = 0;

		virtual void       PreRender();
		virtual void       Render();
		virtual void       PostRender();

		bool               IsEmpty();
		bool               IsDead();

	protected:
		virtual void       RemoveDeadParticles();
	protected:
		IDirect3DDevice9*  m_pD3DDevice;

		D3DXVECTOR3        m_vOrigin;
		CHrBoundingBox*    m_pBoundingBox;

		float              m_fEmitRate;
		float              m_fSize;

		IDirect3DTexture9* m_pTexture;
		IDirect3DVertexBuffer9* m_pVertexBuffer;
		
		std::list<SParticleAttribute*> m_lisParticles;
		
		int                m_nMaxParticles;

		DWORD              m_dwVbNum;        //particle number in vertex buffer
		DWORD              m_dwVbOffset;     //offset in vertex buffer to lock
		DWORD              m_dwVbBatchNum;   //number of vertices to lock starting at m_nVbOffset
	};


}
