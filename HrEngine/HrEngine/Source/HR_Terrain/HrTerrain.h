#pragma once

#include "HrCommon.h"
#include <vector>

namespace HR
{
	class CHrTerrain
	{
	public:
		CHrTerrain();
		~CHrTerrain();

	public:
		void           Initialize(IDirect3DDevice9* pD3DDevice);

		bool           LoadTerrainFromFile(char* pRawFileName, char* pTextureFile);

		bool           InitTerrain(int nRows, int nCols, float fSpace, float fScale);

		bool           RenderTerrain(D3DXMATRIX* pMatWorld, bool bDrawFrame = false);

	private:
		bool           GenerateTexture(D3DXVECTOR3* pDirToLight);

	private:
		IDirect3DDevice9*          m_pD3DDevice;

		std::vector<float>         m_vecHeightInfo;      //��Ÿ߶�i����Ϯ
		IDirect3DTexture9*         m_pTerrainTexture;       

		IDirect3DIndexBuffer9*     m_pIndexBuffer;
		IDirect3DVertexBuffer9*    m_pVertexBuffer;

		int                        m_nRows;              //��Ԫ������
		int                        m_nCols;              //��Ԫ������ 
		int                        m_nVertsPerRow;       //ÿ�еĶ�����
		int                        m_nVertsPerCol;       //ÿ�еĶ�����
		int                        m_nNumVertices;       //��������

		float                      m_fTerrainWidth;      //���εĿ��
		float                      m_fTerrainDepth;      //���ε����
		float                      m_fCellSpacing;       //��Ԫ��ļ��
		float                      m_fHeightScale;       //�߶�����ϵ��

		struct TERRAINVERTEX
		{
			float _x, _y, _z;
			float _u, _v;
			TERRAINVERTEX(float x, float y, float z, float u, float v)
				:_x(x), _y(y), _z(z), _u(u), _v(v){}
			
			static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
		};

	};
}
