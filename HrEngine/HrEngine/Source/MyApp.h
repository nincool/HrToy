#pragma once
#include "HrApplication.h"
#include "HR_D3DUtil/HrD3DUtil.h"

namespace HR
{
	class CHrCamera;
	class CHrMaterial;
	class CHrLight;
	class CHrTexture;
	class CHrHierarchyCtrler;
	class CHrDirectInputTool;
	class CHrTerrain;
	class CHrSnow;
	class CHrBoundingBox;
	class CHrFirework;
	class CHrParticleGun;
}

class CMyApp : public HR::CHrApplication
{
public:
	CMyApp(void);
	~CMyApp(void);

	struct CUSTOMVERTEX
	{
		float x, y, z;
		DWORD color;

		CUSTOMVERTEX(float _x, float _y, float _z, DWORD _color)
		{
			x = _x;
			y = _y;
			z = _z;
			color = _color;
		};
	};
#define D3DFVF_CUSTOMVERTEX  (D3DFVF_XYZ | D3DFVF_DIFFUSE)

	struct CUSTOM_TEXTURE_VERTEX
	{
		float x, y, z;
		float _nx, _ny, _nz;
		float u, v;

		CUSTOM_TEXTURE_VERTEX(D3DXVECTOR3 stVPos, D3DXVECTOR3 stVNormal, float fU, float fV)
		{
			x = stVPos.x; y = stVPos.y; z = stVPos.z;
			_nx = stVNormal.x; _ny = stVNormal.y; _nz = stVNormal.z;
			u = fU;
			v = fV;
		};
	};
#define D3DFVF_CUSTOMTEXTURE (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

public:
	virtual void           UpdateScene();
	
	virtual void           AppSetup();
	
	virtual void           AppRelease();

	virtual void           PreRender();
	virtual void           RenderScene();
	virtual void           PostRender();

private:
	//输入输出
	HR::CHrDirectInputTool* m_pDirectInput;

	int                     m_nUpdateCnt;

	HR::CHrCamera*          m_pMyCamera;
	HR::CHrMaterial*        m_pMyMaterial;
	HR::CHrMaterial*        m_pMyPlaneMaterial;
	HR::CHrLight*           m_pMyLight;
	HR::CHrTexture*         m_pMyTexture;

	HR::CHrTexture*         m_pAlphaTexture;
	HR::CHrTexture*         m_pDetailTexture;
	HR::CHrTexture*         m_pTrueAlphaTexture;
	HR::CHrTexture*         m_pOnePieceTexture;
	HR::CHrTexture*         m_pPlaneTexture;
	//测试灯光是否可以单独影响
	//HR::CHrLight*           m_pMyLight2;

	//骨骼模型
	HR::CHrHierarchyCtrler* m_pHierarchyCtrler;

	HR::CHrTerrain*         m_pTerrain;
	HR::CHrBoundingBox*     m_pBoundingBox;
	HR::CHrSnow*            m_pSnow;
	HR::CHrFirework*        m_pFirework;
	HR::CHrParticleGun*     m_pParticleGun;
};

