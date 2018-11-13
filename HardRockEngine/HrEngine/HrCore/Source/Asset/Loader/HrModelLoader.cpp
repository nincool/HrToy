#include "Asset/Loader/HrModelLoader.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Asset/Loader/HrJsonLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrTexture.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrVertex.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"

using namespace Hr;

HrModelLoader::HrModelLoader()
{
}

HrModelLoader::~HrModelLoader()
{

}

void HrModelLoader::Load(std::string& strFile)
{
	m_strFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	if (m_strFileName.empty())
	{
		HRERROR("HrModelLoader::Load Error! Can not find the file. FileName[%s]", strFile.c_str());
		return;
	}
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(m_strFileName);
	HrStringUtil::ToLowerCase(strSuffix);
	if (strSuffix == "hrmesh")
	{
		std::shared_ptr<HrJsonLoader> pJsonLoader = HrMakeSharedPtr<HrJsonLoader>();
		pJsonLoader->Load(m_strFileName, m_modelDesc);
	}
	else
	{
		TRE("unsuported types!");
		return;
	}


	//construct default vertexelement
	m_pMesh = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMesh>(m_strFileName, true, false);
	BOOST_ASSERT(!m_pMesh->IsLoaded());

	BOOST_ASSERT(m_modelDesc.vecSubMeshInfo.size() == m_modelDesc.vecMaterialDataInfo.size());

	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.vecSubMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nMeshInfoIndex];

		std::vector<HrVertexElement> vecVertexElement;
		MakeVertexElements(subMeshInfo, vecVertexElement);

		//Vertex Buffer
		HrStreamData streamVertexBuffer;
		MakeVertexStream(nMeshInfoIndex, streamVertexBuffer, vecVertexElement);
		
		HrSubMeshPtr pSubMesh = m_pMesh->AddSubMesh(subMeshInfo.strMeshName);
		pSubMesh->GetRenderLayout()->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
		
		//Index Buffer
		HrStreamData streamIndexBuffer;
		MakeIndexStream(nMeshInfoIndex, streamIndexBuffer);
		pSubMesh->GetRenderLayout()->BindIndexBuffer(streamIndexBuffer.GetBufferPoint(), streamIndexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_32BIT);
		

		//todo material
		const HrModelDataInfo::HrMaterialDataInfo& materialInfo = m_modelDesc.vecMaterialDataInfo[nMeshInfoIndex];
		HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMaterial>(subMeshInfo.strMeshName, true, true);
		pMaterial->FillMaterialInfo(materialInfo);
		pSubMesh->SetMaterial(pMaterial);
	}
}

void HrModelLoader::MakeVertexElements(const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo, std::vector<HrVertexElement>& vecVertexElement)
{
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	//if (m_modelDesc.vecTangent.size() > 0)
	//	vecVertexElement.push_back(HrVertexElement(VEU_TANGENT, VET_FLOAT3));
	//if (m_modelDesc.vecBinormal.size() > 0)
	//	vecVertexElement.push_back(HrVertexElement(VEU_BINORMAL, VET_FLOAT3));
	if (subMeshInfo.vecNormal.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	if (subMeshInfo.vecUV.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));
	
}

void HrModelLoader::MakeVertexStream(int nSubMeshIndex, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	Vector3 v3Zero = Vector3::Zero();

	const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nSubMeshIndex];

	for (int nVertexIndex = 0; nVertexIndex < subMeshInfo.vecVertexPos.size(); ++nVertexIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementSemantic)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecVertexPos[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());

				break;
			}
			case VEU_TANGENT:
			{
				break;
			}
			case VEU_BINORMAL:
			{
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecNormal[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_TEXTURE_COORDINATES:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecUV[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}
		}
	}
}

void HrModelLoader::MakeIndexStream(int nSubMeshIndex, HrStreamData& indexData)
{
	const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nSubMeshIndex];
	if (subMeshInfo.vecIndices.size() > 0)
	{
		indexData.AddBuffer((Byte*)(&subMeshInfo.vecIndices[0]), subMeshInfo.vecIndices.size() * sizeof(subMeshInfo.vecIndices[0]));
	}
}

const HrModelDataInfo& HrModelLoader::GetModelDataInfo()
{
	return m_modelDesc;
}
