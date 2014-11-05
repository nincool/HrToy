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

		std::vector<float>         m_vecHeightInfo;      //存放高度i型逆袭
		IDirect3DTexture9*         m_pTerrainTexture;       

		IDirect3DIndexBuffer9*     m_pIndexBuffer;
		IDirect3DVertexBuffer9*    m_pVertexBuffer;

		int                        m_nRows;              //单元格行数
		int                        m_nCols;              //单元格列数 
		int                        m_nVertsPerRow;       //每行的顶点数
		int                        m_nVertsPerCol;       //每列的顶点数
		int                        m_nNumVertices;       //顶点总数

		float                      m_fTerrainWidth;      //地形的宽度
		float                      m_fTerrainDepth;      //地形的深度
		float                      m_fCellSpacing;       //单元格的间距
		float                      m_fHeightScale;       //高度缩放系数

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
