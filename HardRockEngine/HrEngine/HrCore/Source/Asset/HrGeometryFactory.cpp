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
#include "Kernel/HrLog.h"

using namespace Hr;

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
HrGeometryPanel::HrGeometryPanel()
{
	GetBuildInPanelMesh();
}

HrGeometryPanel::~HrGeometryPanel()
{

}

void HrGeometryPanel::GetBuildInPanelMesh()
{
	HrMesh* pPlaneMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(std::string(HR_BUILDIN_RES_PATH) + "PLANEMESH", HrResource::RT_MESH));
	if (!pPlaneMesh->IsLoaded())
	{
		CreatePanelStaticMesh(pPlaneMesh);
	}
}

void HrGeometryPanel::CreatePanelStaticMesh(HrMesh* pMesh)
{
	m_pRenderEffect = static_cast<HrRenderEffect*>(HrResourceManager::Instance()->GetOrLoadResource("HrLambert.effectxml", HrResource::RT_EFFECT));
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");

	Vertex1 vertices[6] =
	{
		{ float3(-100.0f, -100.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },
		{ float3(-100.0f, 100.0f, 0.0f), float3::Zero(), float2(0.0f, 0.0f) },
		{ float3(100.0f, 100.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },

		{ float3(100.0f, 100.0f, 0.0f), float3::Zero(), float2(1.0f, 0.0f) },
		{ float3(100.0f, -100.0f, 0.0f), float3::Zero(), float2(1.0f, 1.0f) },
		{ float3(-100.0f, -100.0f, 0.0f),  float3::Zero(),  float2(0, 1.0f) },

	};

	std::vector<HrVertexElement> vecVertexElemet;
	vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));



	HrSubMesh* pSubMesh = pMesh->AddSubMesh();

	pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);

	pSubMesh->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	std::string strFilePath = "tests\\001Plane.jpg";
	HrTexture* pRes = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strFilePath, HrResource::RT_TEXTURE));
	pSubMesh->SetTexture(pRes);

	m_pSubMesh = pSubMesh;
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
	HrMesh* pBoxMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(std::string(HR_BUILDIN_RES_PATH)+"BOXMESH", HrResource::RT_MESH));
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

	Vertex1 vertices[6] =
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
	std::string strFilePath = "tests\\001Plane.jpg";
	HrTexture* pRes = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strFilePath, HrResource::RT_TEXTURE));
	pSubMesh->SetTexture(pRes);

	m_pSubMesh = pSubMesh;
}

void HrGeometryBox::ComputeNormal(Vertex1* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum)
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
HrGeometrySkyBox::HrGeometrySkyBox()
{
}

HrGeometrySkyBox::~HrGeometrySkyBox()
{

}

bool HrGeometrySkyBox::LoadImpl()
{
	HrMesh* pBoxMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(std::string(HR_BUILDIN_RES_PATH) + "SKYBOXMESH", HrResource::RT_MESH));
	if (!pBoxMesh->IsLoaded())
	{
		CreateSkyBoxStaticMesh(pBoxMesh);
	}

	return true;
}

bool HrGeometrySkyBox::UnloadImpl()
{
	return true;
}

void HrGeometrySkyBox::GetBuildInSkyBoxMesh()
{
}

void HrGeometrySkyBox::CreateSkyBoxStaticMesh(HrMesh* pMesh)
{
	Vertex1 vertices[6];
	float fDistance = 1000.0f;
	std::vector<HrVertexElement> vecVertexElemet;
	vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));

	std::string strTextureFile = "";
	HrTexture* pTexture = nullptr; 

	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_FRONT, vertices, fDistance);
	HrSubMesh* pSubMeshFront = pMesh->AddSubMesh();
	pSubMeshFront->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshFront->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_front.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshFront->SetTexture(pTexture);
	
	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_BACK, vertices, fDistance);
	HrSubMesh* pSubMeshBack = pMesh->AddSubMesh();
	pSubMeshBack->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshBack->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_back.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshBack->SetTexture(pTexture);

	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_LEFT, vertices, fDistance);
	HrSubMesh* pSubMeshLeft = pMesh->AddSubMesh();
	pSubMeshLeft->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshLeft->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_left.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshLeft->SetTexture(pTexture);

	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_RIGHT, vertices, fDistance);
	HrSubMesh* pSubMeshRight = pMesh->AddSubMesh();
	pSubMeshRight->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshRight->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_right.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshRight->SetTexture(pTexture);

	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_UP, vertices, fDistance);
	HrSubMesh* pSubMeshUp = pMesh->AddSubMesh();
	pSubMeshUp->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshUp->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_up.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshUp->SetTexture(pTexture);

	CreateSkyPanelVertice(HrGeometrySkyBox::SPS_BUTTOM, vertices, fDistance);
	HrSubMesh* pSubMeshButtom = pMesh->AddSubMesh();
	pSubMeshButtom->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElemet);
	pSubMeshButtom->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	strTextureFile = "Skybox\\demo1\\sunset_down.png";
	pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	pSubMeshButtom->SetTexture(pTexture);

	m_pMesh = pMesh;
}

void HrGeometrySkyBox::CreateSkyPanelVertice(EnumSkyPlaneSide side, Vertex1* pVertice, float fDistance)
{
	float fHalfDistance = fDistance * 0.5;

	float3 unitZ = float3(0, 0, 1), unitX = float3(1, 0, 0), unitY = float3(0, 1, 0);
	switch (side)
	{
	case HrGeometrySkyBox::SPS_FRONT:
	{
		pVertice[0].position = float3(-fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[0].normal = -unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(-fHalfDistance, fHalfDistance, fHalfDistance); pVertice[1].normal = -unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(fHalfDistance, fHalfDistance, fHalfDistance); pVertice[2].normal = -unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(fHalfDistance, fHalfDistance, fHalfDistance); pVertice[3].normal = -unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[4].normal = -unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(-fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[5].normal = -unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
	case HrGeometrySkyBox::SPS_BACK:
	{
		pVertice[0].position = float3(fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[0].normal = unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[1].normal = unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(-fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[2].normal = unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(-fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[3].normal = unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(-fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[4].normal = unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[5].normal = unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
	case HrGeometrySkyBox::SPS_LEFT:
	{
		pVertice[0].position = float3(-fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[0].normal = unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(-fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[1].normal = unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(-fHalfDistance, fHalfDistance, fHalfDistance); pVertice[2].normal = unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(-fHalfDistance, fHalfDistance, fHalfDistance); pVertice[3].normal = unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(-fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[4].normal = unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(-fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[5].normal = unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
	case HrGeometrySkyBox::SPS_RIGHT:
	{
		pVertice[0].position = float3(fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[0].normal = unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(fHalfDistance, fHalfDistance, fHalfDistance); pVertice[1].normal = unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[2].normal = unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[3].normal = unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[4].normal = unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[5].normal = unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
	case HrGeometrySkyBox::SPS_UP:
	{
		pVertice[0].position = float3(-fHalfDistance, fHalfDistance, fHalfDistance); pVertice[0].normal = unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(-fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[1].normal = unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[2].normal = unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(fHalfDistance, fHalfDistance, -fHalfDistance); pVertice[3].normal = unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(fHalfDistance, fHalfDistance, fHalfDistance); pVertice[4].normal = unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(-fHalfDistance, fHalfDistance, fHalfDistance); pVertice[5].normal = unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
	case HrGeometrySkyBox::SPS_BUTTOM:
	{
		pVertice[0].position = float3(-fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[0].normal = unitZ; pVertice[0].uv = float2(0, 1.0f);
		pVertice[1].position = float3(-fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[1].normal = unitZ; pVertice[1].uv = float2(0, 0.0f);
		pVertice[2].position = float3(fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[2].normal = unitZ; pVertice[2].uv = float2(1.0f, 0.0f);
		pVertice[3].position = float3(fHalfDistance, -fHalfDistance, fHalfDistance); pVertice[3].normal = unitZ; pVertice[3].uv = float2(1.0, 0.0f);
		pVertice[4].position = float3(fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[4].normal = unitZ; pVertice[4].uv = float2(1.0f, 1.0f);
		pVertice[5].position = float3(-fHalfDistance, -fHalfDistance, -fHalfDistance); pVertice[5].normal = unitZ; pVertice[5].uv = float2(0, 1.0f);
		break;
	}
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

HrSceneNode* HrGeometryFactory::CreatePanel()
{
	HrGeometryPanel* pPanel = HR_NEW HrGeometryPanel();
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	pSceneNode->AttachRenderable(pPanel);

	return pSceneNode;
}

HrSceneNode* HrGeometryFactory::CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	HrGeometryBox* pBox = HR_NEW HrGeometryBox();
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	pSceneNode->AttachRenderable(pBox);

	return pSceneNode;
}

HrSceneNode* HrGeometryFactory::CreateSkyBox()
{
	HrPrefabModel* pPrefabModel = static_cast<HrPrefabModel*>(HrResourceManager::Instance()->GetSkyBoxResource("SKYBOX", HrResource::RT_MODEL));
	HRASSERT(pPrefabModel, "CreateSkyBox Error!");

	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	for (size_t i = 0; i < pPrefabModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSkinnedMeshRenderable* pSkinRenderable = HR_NEW HrSkinnedMeshRenderable();
		pSkinRenderable->AttachSubMesh(pPrefabModel->GetMesh()->GetSubMesh(i));
		HrSceneNode* pChildNode = HR_NEW HrSceneNode();
		pSceneNode->AddChild(pChildNode);
		pChildNode->AttachRenderable(pSkinRenderable);
	}
	return pSceneNode;
}

