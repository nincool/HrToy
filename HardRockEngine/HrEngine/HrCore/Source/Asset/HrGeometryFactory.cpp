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
	m_pRenderEffect = static_cast<HrRenderEffect*>(HrResourceManager::Instance()->GetResource("HrLambert.effectxml", HrResource::RT_EFFECT));
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");

	Vertex vertices[8] =
	{
		{ float3(-1.0f, -1.0f, 4.0f),  float3::Zero() },
		{ float3(-1.0f, 1.0f, 4.0f), float3::Zero() },
		{ float3(1.0f, 1.0f, 4.0f), float3::Zero() },
		{ float3(1.0f, -1.0f, 4.0f), float3::Zero() },
		{ float3(-1.0f, -1.0f, 5.0f), float3::Zero() },
		{ float3(-1.0f, 1.0f, 5.0f), float3::Zero() },
		{ float3(1.0f, 1.0f, 5.0f), float3::Zero() },
		{ float3(1.0f, -1.0f, 5.0f), float3::Zero() }
	};

	uint16 indices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 1, 4, 1, 0,
		7, 6, 5, 7, 5, 4,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};

	ComputeNormal(vertices, HR_ARRAY_SIZE(vertices), indices, HR_ARRAY_SIZE(indices));


	HrVertexElement vertexElementArr[] = {
		HrVertexElement(VEU_POSITION, VET_FLOAT3),
		HrVertexElement(VEU_NORMAL, VET_FLOAT3)
	};

	pMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vertexElementArr
		, HR_ARRAY_SIZE(vertexElementArr));


	pMesh->GetRenderLayout()->BindIndexBuffer((char*)indices, sizeof(indices), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);
}

void HrGeometryBox::ComputeNormal(Vertex* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum)
{
	std::vector<Vector3> vecVertexNormal(nVertexNum);
	for (auto& item : vecVertexNormal)
	{
		item = Vector3::Zero();
	}
	for (size_t i = 0; i < nIndexNum; i+=3)
	{
		uint16 nIndex1 = pIndex[i];
		uint16 nIndex2 = pIndex[i + 1];
		uint16 nIndex3 = pIndex[i + 2];

		Vector3 vAB = pVertex[nIndex2].position - pVertex[nIndex1].position;
		Vector3 vAC = pVertex[nIndex3].position - pVertex[nIndex1].position;

		Vector3 vNormal = HrMath::Cross(vAB, vAC);

		vecVertexNormal[nIndex1] += vNormal;
		vecVertexNormal[nIndex2] += vNormal;
		vecVertexNormal[nIndex3] += vNormal;
	}
	
	for (size_t i = 0; i < vecVertexNormal.size(); ++i)
	{
		Vector3 normal = HrMath::Normalize(vecVertexNormal[i]);
		pVertex[i].normal = normal;
	}
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

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

