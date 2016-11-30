#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrMesh.h"
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
		pFBXLoader->Load(strFile, m_strMeshName, m_vecPrimaryPos, m_vecVertexPos, m_vecIndice, m_vecNormal);
	}

	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	if (!m_vecNormal.empty())
	{
		vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	}
	

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

