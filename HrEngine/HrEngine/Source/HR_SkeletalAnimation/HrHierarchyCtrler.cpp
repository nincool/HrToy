#include "HrHierarchyCtrler.h"
#include "HrAllocateHierarchy.h"
#include "HrCommon.h"

#include <string>

using namespace HR;

CHrHierarchyCtrler::CHrHierarchyCtrler(void)
{
	m_pD3DDevice = NULL;

	m_pAllocateHierachy = new CHrAllocateHierarchy();
	m_dwCurTime = 0;
	m_dwLastTime = 0;
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matPosition);
}

CHrHierarchyCtrler::~CHrHierarchyCtrler(void)
{
	SAFE_DELETE(m_pAllocateHierachy);
	SAFE_RELEASE(m_pAnimController);
}

void CHrHierarchyCtrler::Initialize(IDirect3DDevice9* pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

void CHrHierarchyCtrler::CreateHierarchy(const char* pFileName)
{
	//先要判断文件是否存在
	D3DXLoadMeshHierarchyFromX(pFileName
		, D3DXMESH_MANAGED
		, m_pD3DDevice
		, m_pAllocateHierachy
		, NULL
		, &m_pFrameRoot
		, &m_pAnimController);

	//int iSetNum = m_pAnimController->GetNumAnimationSets();
	//for (int i = 0; i < iSetNum; ++i)
	//{
	//	LPD3DXANIMATIONSET pAnimationSet = NULL;
	//	m_pAnimController->GetAnimationSet(i, &pAnimationSet);
	//	std::string strName = pAnimationSet->GetName();
	//}
	
	m_pAllocateHierachy->SetupBoneMatrixPointers(m_pFrameRoot, m_pFrameRoot);
}

void CHrHierarchyCtrler::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	if (pFrameBase == NULL || pParentMatrix == NULL) return;
	D3DXFRAME_DERIVED* pFrame = ( D3DXFRAME_DERIVED* )pFrameBase;

	// 将当前骨骼的相对于父骨骼的偏移矩阵作累积运算
	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);                              // 更新兄弟骨骼
	UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);   // 更新子骨骼
}

void CHrHierarchyCtrler::DrawFrame(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL) return;
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;                    // 取得网格容器
	while( pMeshContainer != NULL )                      
	{
		DrawMeshContainer(m_pD3DDevice, pMeshContainer, pFrame);  // 绘制非空蒙皮网格
		pMeshContainer = pMeshContainer->pNextMeshContainer;    // 遍历所有网格容器
	}

	DrawFrame(pFrame->pFrameSibling);               // 绘制兄弟框架
	DrawFrame(pFrame->pFrameFirstChild);            // 绘制子框架
}

void CHrHierarchyCtrler::DrawMeshContainer(IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = ( D3DXMESHCONTAINER_DERIVED* )pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = ( D3DXFRAME_DERIVED* )pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps( &d3dCaps );

	// first check for skinning
	if( pMeshContainer->pSkinInfo != NULL )
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>( pMeshContainer->pBoneCombinationBuf->GetBufferPointer() );

		// Draw using default vtx processing of the device (typically HW)
		for( iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++ )
		{
			NumBlend = 0;
			for( DWORD i = 0; i < pMeshContainer->NumInfl; ++i )
			{
				if( pBoneComb[iAttrib].BoneId[i] != UINT_MAX )
				{
					NumBlend = i;
				}
			}

			if( d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1 )
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for( DWORD i = 0; i < pMeshContainer->NumInfl; ++i )
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if( iMatrixIndex != UINT_MAX )
					{
						D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
						pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
					}
				}

				pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

				// lookup the material used for this subset of faces
				if( ( AttribIdPrev != pBoneComb[iAttrib].AttribId ) || ( AttribIdPrev == UNUSED32 ) )
				{
					pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
					pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib );
			}
		}
		pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, 0 );
	}
	else  // standard mesh, just draw it after setting material properties
	{
		pd3dDevice->SetTransform( D3DTS_WORLD, &pFrame->CombinedTransformationMatrix );

		for( iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++ )
		{
			pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );
			pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );
			pMeshContainer->MeshData.pMesh->DrawSubset( iMaterial );
		}
	}
}

void CHrHierarchyCtrler::UpdateAnim()
{
	m_dwCurTime = timeGetTime();

	float fTimeDelta = ((float)m_dwCurTime - m_dwLastTime) / 1000;
	m_pAnimController->AdvanceTime(fTimeDelta, NULL);
	m_dwLastTime = m_dwCurTime;

	// 设置骨骼动画的矩阵
	//D3DXMATRIX matFinal = m_matPosition * m_matScale;
	D3DXMATRIX matFinal = m_matScale * m_matPosition;
	//D3DXMatrixMultiply(&m_matPosition, &m_matPosition, &m_matScale);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matFinal);

	UpdateFrameMatrices(m_pFrameRoot, &matFinal);   //更新框架中的变换矩阵
	
}

void CHrHierarchyCtrler::RenderAnim()
{
	DrawFrame(m_pFrameRoot);
}

void CHrHierarchyCtrler::SetScale(D3DXMATRIX matScale)
{
	m_matScale = matScale;
}

void CHrHierarchyCtrler::SetPosition(D3DXMATRIX matPosition)
{
	m_matPosition = matPosition;
}

