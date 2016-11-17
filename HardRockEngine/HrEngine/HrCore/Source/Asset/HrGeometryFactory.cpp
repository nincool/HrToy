#include "Asset/HrGeometryFactory.h"
#include "Asset/HrMesh.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrColor.h"
#include "Asset/HrRenderEffect.h"
#include "Render/HrVertex.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

////////////////////////////////////
//HrGeometryBox
///////////////////////////////////
HrGeometryBox::HrGeometryBox()
{
	GetBuildInBoxMesh();
}

HrGeometryBox::~HrGeometryBox()
{

}

void HrGeometryBox::GetBuildInBoxMesh()
{
	HrMesh* pBoxMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(std::string(HR_BUILDIN_RES_PATH)+"BOXMESH"));
	if (!pBoxMesh->IsLoaded())
	{
		CreateBoxStaticMesh(pBoxMesh);
	}
	m_pMesh = pBoxMesh;
}

void HrGeometryBox::CreateBoxStaticMesh(HrMesh* pMesh)
{
	m_pRenderEffect = static_cast<HrRenderEffect*>(HrResourceManager::Instance()->GetResource("HrBasicEffect.effectxml", HrResource::RT_EFFECT));
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");

	struct Vertex
	{
		float3 position;
		float4 color;
	};

	Vertex vertices[8] =
	{
		{ float3(-1.0f, -1.0f, 4.0f),  HrColor::F4Blue },
		{ float3(-1.0f, 1.0f, 4.0f), HrColor::F4Cyan },
		{ float3(1.0f, 1.0f, 4.0f), HrColor::F4Red },
		{ float3(1.0f, -1.0f, 4.0f), HrColor::F4Yellow },
		{ float3(-1.0f, -1.0f, 5.0f), HrColor::F4Green },
		{ float3(-1.0f, 1.0f, 5.0f), HrColor::F4Silver },
		{ float3(1.0f, 1.0f, 5.0f), HrColor::F4Black },
		{ float3(1.0f, -1.0f, 5.0f), HrColor::F4Magenta }
	};

	HrVertexElement vertexElementArr[] = {
		HrVertexElement(VEU_POSITION, VET_FLOAT3),
		HrVertexElement(VEU_COLOR, VET_FLOAT4)
	};

	pMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vertexElementArr
		, HR_ARRAY_SIZE(vertexElementArr));

	uint16 indices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 1, 4, 1, 0,
		7, 6, 5, 7, 5, 4,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};
	pMesh->GetRenderLayout()->BindIndexBuffer((char*)indices, sizeof(indices), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);

}

HrGeometryFactory::HrGeometryFactory()
{

}

HrGeometryFactory::~HrGeometryFactory()
{
}

HrSceneNode* HrGeometryFactory::CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	HrGeometryBox* pBox = HR_NEW HrGeometryBox();
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode(pBox);

	return pSceneNode;
}

