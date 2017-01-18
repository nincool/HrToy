#include "Asset/HrGeometryFactory.h"
#include "Asset/HrMesh.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrTexture.h"
#include "Render/HrVertex.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;


///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
HrGeometryPlane::HrGeometryPlane()
{

}

HrGeometryPlane::~HrGeometryPlane()
{

}

void HrGeometryPlane::GetBuildInPlaneMesh()
{

}

void HrGeometryPlane::CreateBoxStaticMesh(HrMesh* pMesh)
{

}

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
}

void HrGeometryBox::CreateBoxStaticMesh(HrMesh* pMesh)
{
	m_pRenderEffect = static_cast<HrRenderEffect*>(HrResourceManager::Instance()->GetResource("HrLambert.effectxml", HrResource::RT_EFFECT));
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");

	//Vertex vertices[8] =
	//{
	//	{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f)},
	//	{ float3(-10.0f, 10.0f, 0.0f), float3::Zero(), float2(0.0f, 0.0f) },
	//	{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },
	//	{ float3(10.0f, -10.0f, 0.0f), float3::Zero(), float2(1.0f, 1.0f) },
	//	{ float3(-10.0f, -10.0f, 10.0f), float3::Zero(), float2::Zero() },
	//	{ float3(-10.0f, 10.0f, 10.0f), float3::Zero(), float2::Zero() },
	//	{ float3(10.0f, 10.0f, 10.0f), float3::Zero(), float2::Zero() },
	//	{ float3(10.0f, -10.0f, 10.0f), float3::Zero(), float2::Zero() },
	//};

	Vertex vertices[6] =
	{
		{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f)},
		{ float3(-10.0f, 10.0f, 0.0f), float3::Zero(), float2(0.0f, 0.0f) },
		{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },


		{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },
		{ float3(10.0f, -10.0f, 0.0f), float3::Zero(), float2(1.0f, 1.0f) },
		{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },

	};

	//Vertex vertices[6] =
	//{
	//	{ float3(-10.0f, 10.0f, 0.0f), float3::Zero(), float2(0.0f, 0.0f) },
	//	{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },
	//	{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },

	//	{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },
	//	{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },
	//	{ float3(10.0f, -10.0f, 0.0f), float3::Zero(), float2(1.0f, 1.0f) },
	//};

	//Vertex vertices[3] =
	//{
	//	{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },
	//	{ float3(-10.0f, 10.0f, 0.0f), float3::Zero(), float2(0.0f, 0.0f) },
	//	{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },

		//{ float3(-10.0f, -10.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },
		//{ float3(10.0f, 10.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },
		//{ float3(10.0f, -10.0f, 0.0f), float3::Zero(), float2(1.0f, 1.0f) },
	//};
	//


	//uint16 indices[] =
	//{
	//	0, 1, 2, 0, 2, 3,
	//	4, 5, 1, 4, 1, 0,
	//	7, 6, 5, 7, 5, 4,
	//	3, 2, 6, 3, 6, 7,
	//	1, 5, 6, 1, 6, 2,
	//	4, 0, 3, 4, 3, 7
	//};

	//ComputeNormal(vertices, HR_ARRAY_SIZE(vertices), indices, HR_ARRAY_SIZE(indices));


	//HrVertexElement vertexElementArr[] = {
	//	HrVertexElement(VEU_POSITION, VET_FLOAT3),
	//	HrVertexElement(VEU_NORMAL, VET_FLOAT3),
	//	HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2)
	//};
	std::vector<HrVertexElement> vecVertexElemet;
	vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));

	
	
	HrSubMesh* pSubMesh = pMesh->AddSubMesh();

	pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	//pSubMesh->GetRenderLayout()->BindIndexBuffer((char*)indices, sizeof(indices), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);

	pSubMesh->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	std::string strFilePath = "E:\\Workspace\\HrGitHub\\HrEngineOld\\HardRockEngine\\Bin_Win\\Media\\Model\\tests\\0001.dds";
	HrTexture* pRes = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strFilePath, HrResource::RT_TEXTURE));
	pSubMesh->SetTexture(pRes);

	m_pSubMesh = pSubMesh;
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

		Vector3 vNormal = HrMath::Cross(vAC, vAB);

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
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	pSceneNode->AttachRenderable(pBox);

	return pSceneNode;
}

