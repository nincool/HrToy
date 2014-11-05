#pragma once

#include "../HR_D3DUtil/HrD3DUtil.h"

namespace HR
{
	class CHrAllocateHierarchy;
	class CHrHierarchyCtrler
	{
	public:
		CHrHierarchyCtrler(void);
		~CHrHierarchyCtrler(void);

	public:
		void            Initialize(IDirect3DDevice9* pD3DDevice);
		/**
		*	@Brief: �����㼶�ṹ [4/28/2014 By Hr]
		*/
		void            CreateHierarchy(const char* pFileName);

		/**
		*	@Brief: ���� [4/29/2014 By Hr]
		*/
		void            UpdateAnim();

		void            RenderAnim();

		void            SetScale(D3DXMATRIX matScale);
		void            SetPosition(D3DXMATRIX matPosition);
	public:
		void			UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
		void			DrawFrame(LPD3DXFRAME pFrame);
		void			DrawMeshContainer(IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);

	protected:
		IDirect3DDevice9*           m_pD3DDevice;

		CHrAllocateHierarchy*		m_pAllocateHierachy;
		LPD3DXANIMATIONCONTROLLER   m_pAnimController;
		LPD3DXFRAME                 m_pFrameRoot;

		//ʱ����
		DWORD                       m_dwLastTime;
		DWORD                       m_dwCurTime;

		//������
		D3DXMATRIX                  m_matScale;
		//λ��
		D3DXMATRIX                  m_matPosition;
	};

}
