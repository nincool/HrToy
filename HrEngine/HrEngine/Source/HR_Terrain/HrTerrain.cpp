#include "HrTerrain.h"
#include <fstream>

using namespace HR;
CHrTerrain::CHrTerrain()
{
	m_pD3DDevice = NULL;
}

CHrTerrain::~CHrTerrain()
{
}

void CHrTerrain::Initialize(IDirect3DDevice9* pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

bool CHrTerrain::LoadTerrainFromFile(char* pRawFileName, char* pTextureFile)
{
	//从文件中读取高度信息
	std::ifstream inFile;
	inFile.open(pRawFileName, std::ios::binary);

	inFile.seekg(0, std::ios::end);
	std::vector<BYTE> vecData(inFile.tellg());

	inFile.seekg(std::ios::beg);
	inFile.read((char*)&vecData[0], vecData.size());
	inFile.close();

	m_vecHeightInfo.resize(vecData.size());
	for (uint i = 0; i < vecData.size(); ++i)
	{
		m_vecHeightInfo[i] = vecData[i];
	}

	//加载地形纹理
	//if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, pTextureFile, &m_pTerrainTexture)))
	//{
	//	return FALSE;
	//}
	

	return true;
}

bool CHrTerrain::InitTerrain(int nRows, int nCols, float fSpace, float fScale)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_fCellSpacing = fSpace;
	m_fHeightScale = fScale;            //高度缩放系数

	m_fTerrainWidth = nCols * fSpace;   //地形的宽度
	m_fTerrainDepth = nRows * fSpace;   //地形的深度

	m_nVertsPerRow = m_nCols + 1;       //每行的顶点数
	m_nVertsPerCol = m_nRows + 1;       //每列的顶点数
	m_nNumVertices = m_nVertsPerRow * m_nVertsPerCol; //顶点总数

	for (uint i = 0; i < m_vecHeightInfo.size(); ++i)
	{
		m_vecHeightInfo[i] *= m_fHeightScale;
	}

	if (FAILED(m_pD3DDevice->CreateVertexBuffer(m_nNumVertices * sizeof(TERRAINVERTEX)
		, D3DUSAGE_WRITEONLY, TERRAINVERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0)))
	{
		return false;
	}

	TERRAINVERTEX* pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	float fStartX = -m_fTerrainWidth / 2.0f;
	float fEndX = m_fTerrainWidth / 2.0f;
	float fStartZ = m_fTerrainDepth / 2.0f;
	float fEndZ = -m_fTerrainDepth / 2.0f;
	float fCoordU = 1.0f / (float)m_nCols;
	float fCoordV = 1.0f / (float)m_nRows;

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z > fEndZ; z -= m_fCellSpacing, ++i)
	{
		j = 0;
		for (float x = fStartX; x < fEndX; x += m_fCellSpacing, ++j)
		{
			nIndex = i * m_nCols + j;
			pVertices[nIndex] = TERRAINVERTEX(x, m_vecHeightInfo[nIndex], z, j * fCoordU, i * fCoordV);
			++nIndex;
		}
	}
	m_pVertexBuffer->Unlock();

	if (FAILED(m_pD3DDevice->CreateIndexBuffer(m_nNumVertices * 6 * sizeof(WORD)
		, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
	{
		return false;
	}

	WORD* pIndices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	nIndex = 0;
	for (int nRowIndex = 0; nRowIndex < m_nRows - 1; ++nRowIndex)
	{
		for (int nColIndex = 0; nColIndex < m_nCols - 1; ++nColIndex)
		{
			pIndices[nIndex] = nRowIndex * m_nCols + nColIndex;
			pIndices[nIndex + 1] = nRowIndex * m_nCols + nColIndex + 1;
			pIndices[nIndex + 2] = (nRowIndex + 1) * m_nCols + nColIndex;

			pIndices[nIndex + 3] = (nRowIndex + 1) * m_nCols + nColIndex;
			pIndices[nIndex + 4] = nRowIndex * m_nCols + nColIndex + 1;
			pIndices[nIndex + 5] = (nRowIndex + 1) * m_nCols + nColIndex + 1;

			nIndex += 6;
		}
	}

	m_pIndexBuffer->Unlock();

	GenerateTexture(NULL);

	return true;
}

bool CHrTerrain::RenderTerrain(D3DXMATRIX* pMatWorld, bool bDrawFrame /*= false*/)
{
	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TERRAINVERTEX));
	m_pD3DDevice->SetFVF(TERRAINVERTEX::FVF);
	m_pD3DDevice->SetIndices(m_pIndexBuffer);
	m_pD3DDevice->SetTexture(0, m_pTerrainTexture);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, pMatWorld);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nNumVertices, 0, m_nCols * m_nRows * 2);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pD3DDevice->SetTexture(0, 0);

	return true;
}

bool HR::CHrTerrain::GenerateTexture(D3DXVECTOR3* pDirToLight)
{
	int nTextureWidth = m_nCols - 1;
	int nTextureHeight = m_nRows - 1;

	if (FAILED(D3DXCreateTexture(m_pD3DDevice, nTextureWidth, nTextureHeight, 0, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &m_pTerrainTexture)))
	{
		return false;
	}

	D3DSURFACE_DESC textureDesc;
	m_pTerrainTexture->GetLevelDesc(0, &textureDesc);

	if (textureDesc.Format != D3DFMT_X8R8G8B8)
	{
		return false;
	}

	D3DLOCKED_RECT lockedRect;
	m_pTerrainTexture->LockRect(0, &lockedRect, NULL, 0);

	DWORD* pImageData = (DWORD*)lockedRect.pBits;
	for (int nRow = 0; nRow < nTextureHeight; ++nRow)
	{
		for (int nCol = 0; nCol < nTextureWidth; ++nCol)
		{
			D3DXCOLOR color;

			//获取实际高度
			float fHeight = m_vecHeightInfo[nRow * m_nCols + nCol] / m_fHeightScale;

			if (fHeight < 42.5f)          color = CHrD3DUtil::BEACH_SAND;
			else if (fHeight < 85.0f)     color = CHrD3DUtil::LIGHT_YELLOW_GREEN;
			else if (fHeight < 127.5f)    color = CHrD3DUtil::PUREGREEN;
			else if (fHeight < 170.0f)    color = CHrD3DUtil::DARK_YELLOW_GREEN;
			else if (fHeight < 212.5f)    color = CHrD3DUtil::DARKBROWN;
			else                          color = CHrD3DUtil::WHITE;

			pImageData[nRow * (lockedRect.Pitch / 4) + nCol] = (D3DCOLOR)color;
		}
	}

	m_pTerrainTexture->UnlockRect(0);

	//D3DSURFACE_DESC textureDesc;
	m_pTerrainTexture->GetLevelDesc(0, &textureDesc);

	if (textureDesc.Format != D3DFMT_X8R8G8B8)
	{
		return false;
	}

	//D3DLOCKED_RECT lockedRect;
	m_pTerrainTexture->LockRect(0, &lockedRect, NULL, 0);
	
	//DWORD* pImageData = (DWORD*)lockedRect.pBits;
	pImageData = (DWORD*)lockedRect.pBits;

	D3DXVECTOR3 vLightDir(0.0f, 1.0f, 0.0f);
	for (UINT nRow = 0; nRow < textureDesc.Height; ++nRow)
	{
		for (UINT nCol = 0; nCol < textureDesc.Width; ++nCol)
		{
			int nIndex = nRow * (lockedRect.Pitch / 4) + nCol;

			D3DXCOLOR color(pImageData[nIndex]);

			float fHeightA = m_vecHeightInfo[nRow * m_nCols + nCol] ;
			float fHeightB = m_vecHeightInfo[nRow * m_nCols + nCol + 1] ;
			float fHeightC = m_vecHeightInfo[(nRow + 1) * m_nCols + nCol] ;

			D3DXVECTOR3 u(m_fCellSpacing, fHeightB - fHeightA, 0.0f);
			D3DXVECTOR3 v(0.0f, fHeightC - fHeightA, -m_fCellSpacing);

			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &u, &v);
			D3DXVec3Normalize(&n, &n);

			float fCosine = D3DXVec3Dot(&n, &vLightDir);

			if (fCosine < 0.0f)
			{
				fCosine = 0.0f;
			}

			color *= fCosine;

			pImageData[nIndex] = (D3DCOLOR)color;
		}
	}
	m_pTerrainTexture->UnlockRect(0);

	if (FAILED(D3DXFilterTexture(m_pTerrainTexture, NULL, 0, D3DX_DEFAULT)))
	{
		return false;
	}

	return true;
}


