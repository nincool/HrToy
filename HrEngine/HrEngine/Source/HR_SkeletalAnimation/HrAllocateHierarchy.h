#pragma once
#include "../HR_D3DUtil/HrD3DUtil.h"

namespace HR
{
	//-----------------------------------------------------------------------------
	// Name: struct D3DXFRAME_DERIVED
	// Desc: �̳���DXDXFRAME�ṹ�Ľṹ
	//-----------------------------------------------------------------------------
	struct D3DXFRAME_DERIVED : public D3DXFRAME
	{
		D3DXMATRIXA16 CombinedTransformationMatrix;
	};

	//-----------------------------------------------------------------------------
	// Name: struct D3DXMESHCONTAINER_DERIVED
	// Desc: �̳���D3DXMESHCONTAINER�ṹ�Ľṹ
	//-----------------------------------------------------------------------------
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
	{
		LPDIRECT3DTEXTURE9*  ppTextures;            //��������
		LPD3DXMESH           pOrigMesh;             //ԭʼ����
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD                NumAttributeGroups;    //����������,������������
		DWORD                NumInfl;               //ÿ����������ܶ��ٹ�����Ӱ��
		LPD3DXBUFFER         pBoneCombinationBuf;   //������ϱ�
		D3DXMATRIX**         ppBoneMatrixPtrs;      //��Ź�������ϱ任����
		D3DXMATRIX*          pBoneOffsetMatrices;   //��Ź����ĳ�ʼ�任����
		DWORD                NumPaletteEntries;     //������������
		bool                 UseSoftwareVP;         //��ʶ�Ƿ�ʹ��������㴦��
	};


	class CHrAllocateHierarchy : public ID3DXAllocateHierarchy
	{
	public:
		CHrAllocateHierarchy(void);
		~CHrAllocateHierarchy(void);

	public:
		STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);


		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR              Name,
			CONST D3DXMESHDATA*       pMeshData,
			CONST D3DXMATERIAL*       pMaterials,
			CONST D3DXEFFECTINSTANCE* pEffectInstances,
			DWORD                     NumMaterials,
			CONST DWORD *             pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER *ppNewMeshContainer);

		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);



		HRESULT			AllocateName(LPCSTR Name, LPSTR* pNewName);
		HRESULT			GenerateSkinnedMesh(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer);
		HRESULT			SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	};

}
