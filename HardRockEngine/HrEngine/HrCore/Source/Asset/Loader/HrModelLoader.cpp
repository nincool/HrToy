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
	if (strSuffix == "fbx")
	{
		std::shared_ptr<HrFBXLoader> pFBXLoader = MakeSharedPtr<HrFBXLoader>();
		pFBXLoader->Load(strFile, m_modelDesc);
		BOOST_ASSERT(m_modelDesc.m_vecVertexPos.size() == m_modelDesc.m_vecNormal.size());
	}

	FillEmptyModelInfo();

	//construct default vertexelement
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));

	HrStreamData streamVertexBuffer;
	MakeVertexStream(streamVertexBuffer, vecVertexElement);

	m_pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(HrFileUtils::Instance()->ReplaceFileName(strFile, m_modelDesc.m_strMeshName)));
	HrRenderLayout* pRenderLayout = m_pMesh->GetRenderLayout();
	pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
	pRenderLayout->SetTopologyType(TT_TRIANGLELIST);

	//pRenderLayout->BindVertexBuffer((char*)&m_vecVertexBuffer[0], m_vecVertexBuffer.size() * sizeof(m_vecVertexBuffer[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement[0]);

	//HrVertexElement vertexElementArr[] = {
	//	HrVertexElement(VEU_POSITION, VET_FLOAT3),
	//	HrVertexElement(VEU_COLOR, VET_FLOAT4)
	//};

	//if (!m_vecVertexBuffer.empty() && !m_vecIndexBuffer.empty())
	//{
	//	m_pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(HrFileUtils::Instance()->ReplaceFileName(strFile, m_strMeshName)));
	//	HrRenderLayout* pRenderLayout = m_pMesh->GetRenderLayout();
	//	pRenderLayout->SetTopologyType(TT_TRIANGLELIST);
	//	pRenderLayout->BindVertexBuffer((char*)&m_vecVertexBuffer[0], m_vecVertexBuffer.size() * sizeof(m_vecVertexBuffer[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vertexElementArr, HR_ARRAY_SIZE(vertexElementArr));
	//	pRenderLayout->BindIndexBuffer((char*)&m_vecIndexBuffer[0], m_vecIndexBuffer.size() * sizeof(m_vecIndexBuffer[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_32BIT);
	//}
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
}

void HrModelLoader::MakeVertexStream(HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < m_modelDesc.m_vecVertexPos.size(); ++nIndex)
	{		
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementUsage)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&m_modelDesc.m_vecVertexPos[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
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

