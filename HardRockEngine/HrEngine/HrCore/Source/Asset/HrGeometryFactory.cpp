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
#include "Scene/HrSceneObject.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrLog.h"

using namespace Hr;

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
HrGeometryPlane::HrGeometryPlane(float fWidth, float fHeight)
	:m_fWidth(fWidth), m_fHeight(fHeight)
{
	GetBuildInPlaneMesh();
}

HrGeometryPlane::~HrGeometryPlane()
{

}

void HrGeometryPlane::GetBuildInPlaneMesh()
{
	//HrMeshPtr pPlaneMesh = HrCheckPointerCast<HrMesh>(HrResourceManager::Instance()->RetriveOrAddResource(std::string(HR_BUILDIN_RES_PATH) + "PLANEMESH", HrResource::RT_MESH));
	//if (!pPlaneMesh->IsLoaded())
	//{
	//	CreatePlaneStaticMesh(pPlaneMesh);
	//}
}

void HrGeometryPlane::CreatePlaneStaticMesh(const HrMeshPtr& pMesh)
{
	//todo
	//m_pRenderEffect = HrCheckPointerCast<HrRenderEffect>(HrResourceManager::Instance()->RetriveOrLoadResource("Media/HrShader/HrSimple.json", HrResource::RT_EFFECT));
	//BOOST_ASSERT(m_pRenderEffect);
	//m_pCurTechnique = m_pRenderEffect->GetTechniqueByIndex(0);
	//BOOST_ASSERT(m_pCurTechnique);

	//float fHalfWidth = m_fWidth * 0.5f;
	//float fHalfHeight = m_fHeight * 0.5f;
	//Vertex1 vertices[6] =
	//{
	//	{ float3(-fHalfWidth, -fHalfHeight, 1.0f),  Vector3(0, 0, -1.0f),  float2(0, 1.0f) },
	//	{ float3(-fHalfWidth, fHalfHeight, 1.0f), Vector3(0, 0, -1.0f), float2(0.0f, 0.0f) },
	//	{ float3(fHalfWidth, fHalfHeight, 1.0f), Vector3(0, 0, -1.0f), float2(1.0f, 0.0f) },

	//	{ float3(fHalfWidth, fHalfHeight, 1.0f), Vector3(0, 0, -1.0f), float2(1.0f, 0.0f) },
	//	{ float3(fHalfWidth, -fHalfHeight, 1.0f), Vector3(0, 0, -1.0f), float2(1.0f, 1.0f) },
	//	{ float3(-fHalfWidth, -fHalfHeight, 1.0f),  Vector3(0, 0, -1.0f),  float2(0, 1.0f) },

	//};

	//std::vector<HrVertexElement> vecVertexElemet;
	//vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));

	//const HrSubMeshPtr& pSubMesh = pMesh->AddSubMesh("plane");

	//pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);

	//pSubMesh->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//m_pSubMesh = pSubMesh;
	//pMesh->Load();
}

////////////////////////////////////
//HrGeometryBox
///////////////////////////////////
HrGeometryBox::HrGeometryBox(float fLength)
	:m_fLength(fLength)
{
	GetBuildInBoxMesh();
}

HrGeometryBox::~HrGeometryBox()
{
}

void HrGeometryBox::GetBuildInBoxMesh()
{
	//HrMesh* pBoxMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(std::string(HR_BUILDIN_RES_PATH)+"BOXMESH", HrResource::RT_MESH));
	//if (!pBoxMesh->IsLoaded())
	//{
	//	CreateBoxStaticMesh(pBoxMesh);
	//}
}

void HrGeometryBox::CreateBoxStaticMesh(HrMesh* pMesh)
{
	//m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	//BOOST_ASSERT(m_pRenderEffect);
	//m_pRenderTechnique = m_pRenderEffect->GetTechniqueByIndex(0);
	//BOOST_ASSERT(m_pRenderTechnique);

	//float fHalfLength = m_fLength * 0.5f;
	//Vertex1 vertices[] =
	//{
	//	//front
	//	{ float3(-fHalfLength, -fHalfLength, -fHalfLength),  Vector3(0.0f, 0.0f, -1.0f),  float2(0, 1.0f)},
	//	{ float3(-fHalfLength, fHalfLength, -fHalfLength), Vector3(0.0f, 0.0f, -1.0f), float2(0.0f, 0.0f) },
	//	{ float3(fHalfLength, fHalfLength, -fHalfLength), Vector3(0.0f, 0.0f, -1.0f), float2(1.0f, 0.0f) },

	//	{ float3(fHalfLength, fHalfLength, -fHalfLength), Vector3(0.0f, 0.0f, -1.0f), float2(1.0f, 0.0f) },
	//	{ float3(fHalfLength, -fHalfLength, -fHalfLength), Vector3(0.0f, 0.0f, -1.0f), float2(1.0f, 1.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, -fHalfLength), Vector3(0.0f, 0.0f, -1.0f),  float2(0, 1.0f) },

	//	//right
	//	{ float3(fHalfLength, -fHalfLength, -fHalfLength),  Vector3(1.0f, 0.0f, 0.0f),  float2(0, 1.0f) },
	//	{ float3(fHalfLength, fHalfLength, -fHalfLength), Vector3(1.0f, 0.0f, 0.0f), float2(0.0f, 0.0f) },
	//	{ float3(fHalfLength, fHalfLength, fHalfLength), Vector3(1.0f, 0.0f, 0.0f), float2(1.0f, 0.0f) },

	//	{ float3(fHalfLength, fHalfLength, fHalfLength), Vector3(1.0f, 0.0f, 0.0f), float2(1.0f, 0.0f) },
	//	{ float3(fHalfLength, -fHalfLength, fHalfLength), Vector3(1.0f, 0.0f, 0.0f), float2(1.0f, 1.0f) },
	//	{ float3(fHalfLength, -fHalfLength, -fHalfLength), Vector3(1.0f, 0.0f, 0.0f),  float2(0, 1.0f) },

	//	//left
	//	{ float3(-fHalfLength, -fHalfLength, fHalfLength),  Vector3(-1.0f, 0.0f, 0.0f),  float2(0, 1.0f) },
	//	{ float3(-fHalfLength, fHalfLength, fHalfLength), Vector3(-1.0f, 0.0f, 0.0f), float2(0.0f, 0.0f) },
	//	{ float3(-fHalfLength, fHalfLength, -fHalfLength), Vector3(-1.0f, 0.0f, 0.0f), float2(1.0f, 0.0f) },

	//	{ float3(-fHalfLength, fHalfLength, -fHalfLength), Vector3(-1.0f, 0.0f, 0.0f), float2(1.0f, 0.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, -fHalfLength), Vector3(-1.0f, 0.0f, 0.0f), float2(1.0f, 1.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, fHalfLength), Vector3(-1.0f, 0.0f, 0.0f),  float2(0, 1.0f) },

	//	//back
	//	{ float3(fHalfLength, -fHalfLength, fHalfLength),  Vector3(0.0f, 0.0f, 1.0f),  float2(0, 1.0f)},
	//	{ float3(fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 0.0f, 1.0f), float2(0.0f, 0.0f) },
	//	{ float3(-fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 0.0f, 1.0f), float2(1.0f, 0.0f) },

	//	{ float3(-fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 0.0f, 1.0f), float2(1.0f, 0.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, fHalfLength), Vector3(0.0f, 0.0f, 1.0f), float2(1.0f, 1.0f) },
	//	{ float3(fHalfLength, -fHalfLength, fHalfLength), Vector3(0.0f, 0.0f, 1.0f),  float2(0, 1.0f) },

	//	//top
	//	{ float3(-fHalfLength, fHalfLength, -fHalfLength),  Vector3(0.0f, 1.0f, 0.0f),  float2(0, 1.0f) },
	//	{ float3(-fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 1.0f, 0.0f), float2(0.0f, 0.0f) },
	//	{ float3(fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 1.0f, 0.0f), float2(1.0f, 0.0f) },

	//	{ float3(fHalfLength, fHalfLength, fHalfLength), Vector3(0.0f, 1.0f, 0.0f), float2(1.0f, 0.0f) },
	//	{ float3(fHalfLength, fHalfLength, -fHalfLength), Vector3(0.0f, 1.0f, 0.0f), float2(1.0f, 1.0f) },
	//	{ float3(-fHalfLength, fHalfLength, -fHalfLength), Vector3(0.0f, 1.0f, 0.0f),  float2(0, 1.0f) },

	//	//buttom
	//	{ float3(-fHalfLength, -fHalfLength, fHalfLength),  Vector3(0.0f, -1.0f, 0.0f),  float2(0, 1.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, -fHalfLength), Vector3(0.0f, -1.0f, 0.0f), float2(0.0f, 0.0f) },
	//	{ float3(fHalfLength, -fHalfLength, -fHalfLength), Vector3(0.0f, -1.0f, 0.0f), float2(1.0f, 0.0f) },

	//	{ float3(fHalfLength, -fHalfLength, -fHalfLength), Vector3(0.0f, -1.0f, 0.0f), float2(1.0f, 0.0f) },
	//	{ float3(fHalfLength, -fHalfLength, fHalfLength), Vector3(0.0f, -1.0f, 0.0f), float2(1.0f, 1.0f) },
	//	{ float3(-fHalfLength, -fHalfLength, fHalfLength), Vector3(0.0f, -1.0f, 0.0f),  float2(0, 1.0f) },
	//};


	//std::vector<HrVertexElement> vecVertexElemet;
	//vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));

	//
	//HrSubMesh* pSubMesh = pMesh->AddSubMesh();
	//pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMesh->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());

	//m_pSubMesh = pSubMesh;
}

//void HrGeometryBox::ComputeNormal(Vertex1* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum)
//{
//	std::vector<Vector3> vecVertexNormal(nVertexNum);
//	for (auto& item : vecVertexNormal)
//	{
//		item = Vector3::Zero();
//	}
//	for (size_t i = 0; i < nIndexNum; i+=3)
//	{
//		uint16 nIndex1 = pIndex[i];
//		uint16 nIndex2 = pIndex[i + 1];
//		uint16 nIndex3 = pIndex[i + 2];
//
//		Vector3 vAB = pVertex[nIndex2].position - pVertex[nIndex1].position;
//		Vector3 vAC = pVertex[nIndex3].position - pVertex[nIndex1].position;
//
//		Vector3 vNormal = HrMath::Cross(vAC, vAB);
//
//		vecVertexNormal[nIndex1] += vNormal;
//		vecVertexNormal[nIndex2] += vNormal;
//		vecVertexNormal[nIndex3] += vNormal;
//	}
//	
//	for (size_t i = 0; i < vecVertexNormal.size(); ++i)
//	{
//		Vector3 normal = HrMath::Normalize(vecVertexNormal[i]);
//		pVertex[i].normal = normal;
//	}
//}

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
	//HrMesh* pBoxMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(std::string(HR_BUILDIN_RES_PATH) + "SKYBOXMESH", HrResource::RT_MESH));
	//if (!pBoxMesh->IsLoaded())
	//{
	//	CreateSkyBoxStaticMesh(pBoxMesh);
	//}

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
	//Vertex1 vertices[6];
	//float fDistance = 1000.0f;
	//std::vector<HrVertexElement> vecVertexElemet;
	//vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	//vecVertexElemet.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));

	//std::string strTextureFile = "";
	//HrTexture* pTexture = nullptr; 

	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_FRONT, vertices, fDistance);
	//HrSubMesh* pSubMeshFront = pMesh->AddSubMesh();
	//pSubMeshFront->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshFront->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_front.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshFront->SetTexture(pTexture);
	//
	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_BACK, vertices, fDistance);
	//HrSubMesh* pSubMeshBack = pMesh->AddSubMesh();
	//pSubMeshBack->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshBack->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_back.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshBack->SetTexture(pTexture);

	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_LEFT, vertices, fDistance);
	//HrSubMesh* pSubMeshLeft = pMesh->AddSubMesh();
	//pSubMeshLeft->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshLeft->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_left.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshLeft->SetTexture(pTexture);

	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_RIGHT, vertices, fDistance);
	//HrSubMesh* pSubMeshRight = pMesh->AddSubMesh();
	//pSubMeshRight->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshRight->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_right.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshRight->SetTexture(pTexture);

	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_UP, vertices, fDistance);
	//HrSubMesh* pSubMeshUp = pMesh->AddSubMesh();
	//pSubMeshUp->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshUp->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_up.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshUp->SetTexture(pTexture);

	//CreateSkyPlaneVertice(HrGeometrySkyBox::SPS_BUTTOM, vertices, fDistance);
	//HrSubMesh* pSubMeshButtom = pMesh->AddSubMesh();
	//pSubMeshButtom->GetRenderLayout()->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vecVertexElemet);
	//pSubMeshButtom->SetMaterial(HrResourceManager::Instance()->GetDefaultMaterial());
	//strTextureFile = "Skybox\\demo1\\sunset_down.png";
	//pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->RetriveOrLoadResource(strTextureFile, HrResource::RT_TEXTURE));
	//pSubMeshButtom->SetTexture(pTexture);

	//m_pMesh = pMesh;
}

void HrGeometrySkyBox::CreateSkyPlaneVertice(EnumSkyPlaneSide side, Vertex1* pVertice, float fDistance)
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

HrSceneNodePtr HrGeometryFactory::CreatePlane(float fWidth, float fHeight)
{
	std::shared_ptr<HrGeometryPlane> pPlane = HrMakeSharedPtr<HrGeometryPlane>(fWidth, fHeight);
	HrSceneObjectPtr pPlaneObj = HrMakeSharedPtr<HrSceneObject>(pPlane);
	HrSceneNodePtr pPlaneNode = HrMakeSharedPtr<HrSceneNode>("plane");
	pPlaneNode->SetSceneObject(pPlaneObj);

	return pPlaneNode;
}

HrSceneNode* HrGeometryFactory::CreateBox(float fLength)
{
	HrGeometryBox* pBox = HR_NEW HrGeometryBox(fLength);
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	//pSceneNode->AttachRenderable(pBox);

	return pSceneNode;
}

HrSceneNode* HrGeometryFactory::CreateSkyBox()
{
	//HrModel* pPrefabModel = static_cast<HrModel*>(HrResourceManager::Instance()->GetSkyBoxResource("SKYBOX", HrResource::RT_MODEL));
	//HRASSERT(pPrefabModel, "CreateSkyBox Error!");

	//HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	//for (size_t i = 0; i < pPrefabModel->GetMesh()->GetSubMeshNum(); ++i)
	//{
	//	HrSkinnedMeshRenderable* pSkinRenderable = HR_NEW HrSkinnedMeshRenderable();
	//	pSkinRenderable->AttachSubMesh(pPrefabModel->GetMesh()->GetSubMesh(i));
	//	HrSceneNode* pChildNode = HR_NEW HrSceneNode();
	//	pSceneNode->AddChild(pChildNode);
	//	pChildNode->AttachRenderable(pSkinRenderable);
	//}
	//return pSceneNode;

	return nullptr;
}

