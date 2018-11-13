#include "Asset/HrMeshModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrStreamData.h"
#include "Asset/Loader/HrModelLoader.h"
#include "Render/HrVertex.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrFileUtils.h"

using namespace Hr;

std::vector<HrVertexElement> SVertexStructP::m_s_vecVertexElementP;
std::vector<HrVertexElement> SVertexStructPC::m_s_vecVertexElementPC;
std::vector<HrVertexElement> SVertexStructPN::m_s_vecVertexElementPN;
std::vector<HrVertexElement> SVertexStructPNC::m_s_vecVertexElementPNC;

SVertexStructP::SVertexStructP() : m_position(float3::Zero())
{
	if (m_s_vecVertexElementP.empty())
	{
		m_s_vecVertexElementP.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	}
}

SVertexStructPC::SVertexStructPC() : m_tex(float2::Zero())
{
	if (m_s_vecVertexElementPC.empty())
	{
		m_s_vecVertexElementPC.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
		m_s_vecVertexElementPC.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));
	}
}

SVertexStructPN::SVertexStructPN() : m_normal(float3::Zero())
{
	if (m_s_vecVertexElementPN.empty())
	{
		m_s_vecVertexElementPN.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
		m_s_vecVertexElementPN.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	}
}

SVertexStructPNC::SVertexStructPNC() : m_tex(float2(0.0f, 0.0f))
{
	if (m_s_vecVertexElementPNC.empty())
	{
		m_s_vecVertexElementPNC.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
		m_s_vecVertexElementPNC.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
		m_s_vecVertexElementPNC.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));
	}
}

/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

size_t HrMeshModel::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrMeshModel::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFileName = strFileName;
	if (strFilePath.empty())
		m_strFilePath = strFileName;
	else
		m_strFilePath = strFilePath;
	m_resType = HrResource::RT_MESHMODEL;
	m_resStatus = HrResource::RS_DECLARED;

	m_nHashID = CreateHashName(m_strFilePath);
}

const HrMeshPtr& HrMeshModel::GetMesh() const
{
	return m_pMesh;
}

bool HrMeshModel::LoadImpl()
{
	m_resStatus = HrResource::RS_LOADED;

	return true;
}

bool HrMeshModel::UnloadImpl()
{
	//todo

	return true;
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrMeshModelQuadP::HrMeshModelQuadP(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	CreateQuadMesh();
}

HrMeshModelQuadP::~HrMeshModelQuadP()
{
}

void HrMeshModelQuadP::CreateQuadMesh()
{
	auto pResCom = HrDirector::Instance()->GetResourceModule();

	m_pMesh = HrMakeSharedPtr<HrMesh>();
	{
		//why 0? because i want to sign the submesh's pos in the array
		const HrSubMeshPtr& pSubMesh = m_pMesh->AddSubMesh("0_Quad");
		{
			float fHalfWidth = m_fWidth / 2;
			float fHalfHeight = m_fHeight / 2;

			SVertexStructP vertexData[4];
			vertexData[0].m_position = float3(-fHalfWidth, fHalfHeight, 0);
			vertexData[1].m_position = float3(fHalfWidth, fHalfHeight, 0);
			vertexData[2].m_position = float3(fHalfWidth, -fHalfHeight, 0);
			vertexData[3].m_position = float3(-fHalfWidth, -fHalfHeight, 0);
			
			//Build vertexbuffer
			pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)vertexData
				, sizeof(vertexData) 
				, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
				, SVertexStructP::m_s_vecVertexElementP);
		}

		{
			//Build indexbuffer
			unsigned short indices[6] = { 0, 1, 2, 0, 2, 3 };
			
			pSubMesh->GetRenderLayout()->BindIndexBuffer(reinterpret_cast<char*>(indices)
				, sizeof(indices)
				, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
				, IT_16BIT);
		}
		pSubMesh->GetRenderLayout()->SetTopologyType(TT_TRIANGLELIST);

		auto pMaterial = pResCom->RetriveResource<HrMaterial>();
		m_mapMaterials[pSubMesh->GetName()] = pMaterial;
		//todo
		pSubMesh->SetMaterial(pMaterial);
	}
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrMeshModelGrid::HrMeshModelGrid()
{
	m_nSteps = 100;
	m_fStepLong = 30.0f;


}

HrMeshModelGrid::~HrMeshModelGrid()
{

}

bool HrMeshModelGrid::LoadImpl()
{
	CreateGridMesh();

	m_resStatus = HrResource::RS_LOADED;

	return true;
}

void HrMeshModelGrid::CreateGridMesh()
{
	auto pResCom = HrDirector::Instance()->GetResourceModule();

	m_pMesh = pResCom->RetriveResource<HrMesh>("BuildIn_GridMesh", true, false);
	if (!m_pMesh->IsLoaded())
	{
		auto pDefualtEff = pResCom->RetriveResource<HrRenderEffect>();

		uint32 nLinesCount = m_nSteps + 1;
		//why 0? because i want to sign the submesh's pos in the array
		const HrSubMeshPtr& pSubMesh = m_pMesh->AddSubMesh("0_Grid");
		{
			SGridVertex* pVertexBuff = new SGridVertex[nLinesCount * nLinesCount];
			float fWidth = m_nSteps * m_fStepLong;
			float fStartX = -fWidth * 0.5f;
			float fStartZ = fWidth * 0.5f;
			for (int nRowIndex = 0; nRowIndex < nLinesCount; ++nRowIndex)
			{
				for (int nColIndex = 0; nColIndex < nLinesCount; ++nColIndex)
				{
					int nIndexVertex = nRowIndex * nLinesCount + nColIndex;
					pVertexBuff[nIndexVertex].position = Vector3(fStartX + m_fStepLong * nColIndex, 0.0f, fStartZ - nRowIndex * m_fStepLong);
					pVertexBuff[nIndexVertex].normal = Vector3::Zero();
				}
			}

			std::vector<HrVertexElement> vecVertexElemet;
			vecVertexElemet.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
			vecVertexElemet.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));

			//Build vertexbuffer
			pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)pVertexBuff
				, sizeof(SGridVertex) * nLinesCount * nLinesCount
				, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
				, vecVertexElemet);

			delete pVertexBuff;
			pVertexBuff = nullptr;
		}
		
		{
			//Build indexbuffer
			uint32 nIndicesCount = (nLinesCount - 1) * 2 * nLinesCount * 2;
			unsigned short* pIndices = new unsigned short[nIndicesCount];
			int nPlanIndex = 0;
			for (int nRowIndex = 0; nRowIndex < nLinesCount; ++nRowIndex)
			{
				for (int nColIndex = 0; nColIndex < nLinesCount; ++nColIndex)
				{
					if (nColIndex != nLinesCount - 1)
					{
						pIndices[nPlanIndex++] = nRowIndex * nLinesCount + nColIndex;
						pIndices[nPlanIndex++] = nRowIndex * nLinesCount + nColIndex + 1;
					}
					if (nRowIndex != nLinesCount - 1)
					{
						pIndices[nPlanIndex++] = nRowIndex * nLinesCount + nColIndex;
						pIndices[nPlanIndex++] = (nRowIndex + 1) * nLinesCount + nColIndex;
					}

				}
			}
			pSubMesh->GetRenderLayout()->BindIndexBuffer(reinterpret_cast<char*>(pIndices)
				, nIndicesCount * sizeof(pIndices[0])
				, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
				, IT_16BIT);

			delete pIndices;
			pIndices = nullptr;
		}

		pSubMesh->GetRenderLayout()->SetTopologyType(TT_LINELIST);

		auto pMaterial = pResCom->RetriveResource<HrMaterial>();
		m_mapMaterials[pSubMesh->GetName()] = pMaterial;
		//todo
		pSubMesh->SetMaterial(pMaterial);

		//set m_resStatus to RS_LOADED
		m_pMesh->Load();

	}
}


///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrMeshModelObject::HrMeshModelObject()
{

}

HrMeshModelObject::~HrMeshModelObject()
{

}

bool HrMeshModelObject::LoadImpl()
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(m_strFilePath);
	if (strFullPath.length() <= 0)
	{
		HRERROR("HrMeshModelObject::LoadImpl Error! FileName[%s]", m_strFilePath.c_str());
		return false;
	}

	{
		m_pModelLoader = std::make_shared<HrModelLoader>();
		m_pModelLoader->Load(strFullPath);
		m_pMesh = m_pModelLoader->GetMesh();
		m_pMesh->Retain(); //add Referrence
	}
}

bool HrMeshModelObject::UnloadImpl()
{
	if (m_pMesh)
	{
		HrDirector::Instance()->GetResourceModule()->RemoveResource<HrMesh>(m_pMesh->GetFilePath());
	}

	m_pMesh = nullptr;

	return true;
}

const HrModelLoaderPtr& HrMeshModelObject::GetModelLoader()
{
	return m_pModelLoader;
}
