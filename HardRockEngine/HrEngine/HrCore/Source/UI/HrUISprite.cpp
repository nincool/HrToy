#include "UI/HrUISprite.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
#include "Render/HrVertex.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"


using namespace Hr;

HrUISprite::HrUISprite(const std::string& strFileName)
{
	m_pTexture = HrDirector::Instance()->GetResourceModule()->RetriveTexture(strFileName, HrTexture::TEX_TYPE_2D);
	InitWidthTexture(m_pTexture);
}

HrUISprite::~HrUISprite()
{

}

void HrUISprite::Render()
{

}

bool HrUISprite::InitWidthTexture(const HrTexturePtr& pTexture)
{
	m_pTexture = pTexture;
	m_fWidth = m_pTexture->GetWidth();
	m_fHeight = m_pTexture->GetHeight();
	
	//todo
	RebuildQuad();

	return true;
}

void HrUISprite::RebuildQuad()
{
	m_pMesh = HrMakeSharedPtr<HrMesh>();
	m_pMesh->DeclareResource("Buildin_GridMesh", "Buildin_GridMesh");
	
	const HrSubMeshPtr& pSubMesh = m_pMesh->AddSubMesh("0_UIWidget_Quad");
	m_quad.m_vecVertices[0].m_position = float3(0, 0, 0);
	m_quad.m_vecVertices[0].m_tex = float2(0, 1);
	m_quad.m_vecVertices[1].m_position = float3(0, m_fHeight, 0);
	m_quad.m_vecVertices[1].m_tex = float2(0, 0);
	m_quad.m_vecVertices[2].m_position = float3(m_fWidth, m_fHeight, 0);
	m_quad.m_vecVertices[2].m_tex = float2(1, 0);
	m_quad.m_vecVertices[3].m_position = float3(m_fWidth, 0, 0);
	m_quad.m_vecVertices[3].m_tex = float2(1, 1);

	//Build vertexbuffer
	pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)m_quad.m_vecVertices
		, sizeof(m_quad.m_vecVertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, SVertexStruct_P_UV::m_s_vecVertexElement_P_UV);

	pSubMesh->SetMeshAABB(AABBox(Vector3(0, 0, 0), Vector3(m_fWidth, m_fHeight, 0)));
	
	{
		//Build indexbuffer
		unsigned short indices[6] = { 0, 1, 2, 0, 2, 3 };

		pSubMesh->GetRenderLayout()->BindIndexBuffer(reinterpret_cast<char*>(indices)
			, sizeof(indices)
			, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
			, IT_16BIT);
	}

	pSubMesh->GetRenderLayout()->SetTopologyType(TT_TRIANGLELIST);
	auto pMaterial = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMaterial>();
	pMaterial->SetTexture(HrMaterial::TS_ALBEDO, m_pTexture);
	//todo
	pSubMesh->SetMaterial(pMaterial);

	m_pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>(pSubMesh);

}




