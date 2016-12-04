#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"

using namespace Hr;

HrModelLoader::HrModelLoader()
{
	m_pMesh = nullptr;
}

HrModelLoader::~HrModelLoader()
{

}

void HrModelLoader::Load(std::string& strFile)
{
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
	HrStringUtil::ToLowerCase(strSuffix);
	if (strSuffix == "fbx")
	{
		std::shared_ptr<HrFBXLoader> pFBXLoader = MakeSharedPtr<HrFBXLoader>();
		pFBXLoader->Load(strFile, m_modelDesc);
	}

	FillEmptyModelInfo();

	//construct default vertexelement
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));

	HrStreamData streamVertexBuffer;
	MakeVertexStream(streamVertexBuffer, vecVertexElement);
	HrStreamData streadIndexBuffer;

	m_pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(HrFileUtils::Instance()->ReplaceFileName(strFile, m_modelDesc.m_strMeshName)));
	HrRenderLayout* pRenderLayout = m_pMesh->GetRenderLayout();
	pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
	pRenderLayout->SetTopologyType(TT_TRIANGLELIST);

	if (m_modelDesc.m_vecIndice.size() > 0)
	{
		pRenderLayout->BindIndexBuffer((const char*)(&m_modelDesc.m_vecIndice[0]), m_modelDesc.m_vecIndice.size() * sizeof(m_modelDesc.m_vecIndice[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);
	}
}

void HrModelLoader::FillEmptyModelInfo()
{
	BOOST_ASSERT(!m_modelDesc.m_vecPrimaryPos.empty());
	BOOST_ASSERT(!m_modelDesc.m_vecVertexPos.empty());
	if (m_modelDesc.m_vecColor.empty())
	{
		for (size_t i = 0; i < m_modelDesc.m_vecVertexPos.size(); ++i)
		{
			m_modelDesc.m_vecColor.push_back(HrColor::White.Value());
		}
	}
	CalculateAverageNormals();
}

void HrModelLoader::MakeVertexStream(HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < m_modelDesc.m_vecPrimaryPos.size(); ++nIndex)
	{		
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementUsage)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&m_modelDesc.m_vecPrimaryPos[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)&(m_modelDesc.m_vecNormal[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_COLOR:
			{
				streamData.AddBuffer((Byte*)&(m_modelDesc.m_vecColor[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}

		}
	}
}

void HrModelLoader::CalculateAverageNormals()
{
	if (m_modelDesc.m_vecVertexPos.size() > 0 && m_modelDesc.m_vecNormal.empty())
	{
		m_modelDesc.m_vecNormal.reserve(m_modelDesc.m_vecPrimaryPos.size());
		for (size_t i = 0; i < m_modelDesc.m_vecPrimaryPos.size(); ++i)
		{
			m_modelDesc.m_vecNormal.push_back(Vector3::Zero());
		}
		for (size_t i = 0; i < m_modelDesc.m_vecIndice.size(); i += 3)
		{
			uint16 nIndex1 = m_modelDesc.m_vecIndice[i];
			uint16 nIndex2 = m_modelDesc.m_vecIndice[i + 1];
			uint16 nIndex3 = m_modelDesc.m_vecIndice[i + 2];

			Vector3 vAB = m_modelDesc.m_vecPrimaryPos[nIndex2] - m_modelDesc.m_vecPrimaryPos[nIndex1];
			Vector3 vAC = m_modelDesc.m_vecPrimaryPos[nIndex3] - m_modelDesc.m_vecPrimaryPos[nIndex1];

			Vector3 vNormal = HrMath::Cross(vAC, vAB);

			m_modelDesc.m_vecNormal[nIndex1] += vNormal;
			m_modelDesc.m_vecNormal[nIndex2] += vNormal;
			m_modelDesc.m_vecNormal[nIndex3] += vNormal;
		}
		for (size_t i = 0; i < m_modelDesc.m_vecNormal.size(); ++i)
		{
			m_modelDesc.m_vecNormal[i] = HrMath::Normalize(m_modelDesc.m_vecNormal[i]);
		}
	}
}

