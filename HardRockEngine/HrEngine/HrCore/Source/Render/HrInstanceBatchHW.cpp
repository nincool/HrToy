#include "Render/HrInstanceBatchHW.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrInstanceBatchObject.h"
#include "Render/HrRenderFrameParameters.h"
#include "Asset/HrMesh.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"


using namespace Hr;

HrInstanceBatchHW::HrInstanceBatchHW()
{

}

HrInstanceBatchHW::~HrInstanceBatchHW()
{

}

void HrInstanceBatchHW::BuildVertices(const HrSubMeshPtr& pSubMesh)
{
	m_pBatchRenderLayout = HrDirector::Instance()->GetRenderComponent()->GetRenderFactory()->CreateRenderLayout();
	const HrRenderLayoutPtr& pBaseRenderLayout = pSubMesh->GetRenderLayout();
	m_pBatchRenderLayout->SetTopologyType(pBaseRenderLayout->GetTopologyType());

	const std::vector<HrVertexDataPtr>& vecBaseVertexStreams = pBaseRenderLayout->GetVertexStreams();
	for (size_t i = 0; i < vecBaseVertexStreams.size(); ++i)
	{
		const HrVertexDataPtr& pVertexData = vecBaseVertexStreams[i];
		m_pBatchRenderLayout->BindVertexBuffer(pVertexData->GetVertexBaseData()->GetBufferPoint()
			, pVertexData->GetVertexBaseData()->GetBufferSize()
			, HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE
			, pVertexData->GetVertex()->GetVertexElement());
	}

	//float instance : TEXCOORD1
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT1, VEC_INSTANCE, m_pBatchRenderLayout->GetNextVertexSemanticIndex(VEU_TEXTURE_COORDINATES), 1));

	std::vector<float> vecInstanceData;
	vecInstanceData.reserve(HR_MAX_INSTANCE_NUM);
	for (size_t i = 0; i < HR_MAX_INSTANCE_NUM; ++i)
	{
		vecInstanceData.push_back(static_cast<float>(i));
	}

	m_pBatchRenderLayout->BindVertexBuffer(reinterpret_cast<char*>(&vecInstanceData[0])
		, vecInstanceData.size() * sizeof(float)
		, HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE
		, vecVertexElement);
}

HrSceneObjectPtr HrInstanceBatchHW::CreateInstance()
{
	HrSceneObjectPtr pInsBatchObj = HrMakeSharedPtr<HrSceneObject>();
	m_vecInstanceObjects.emplace_back(pInsBatchObj);
	m_pBatchRenderLayout->SetInstanceNum(m_vecInstanceObjects.size());

	return pInsBatchObj;
}

void HrInstanceBatchHW::OnRenderBegin()
{
	HrInstanceBatch::OnRenderBegin();

	auto pRenderParam = m_pRenderEffect->GetParameterByName("world_matrix_array");
	BOOST_ASSERT(pRenderParam);

	std::vector<float4x4> vecWordMatrix;
	for (size_t i = 0; i < m_vecInstanceObjects.size(); ++i)
	{
		auto pSceneNode = m_vecInstanceObjects[i]->GetSceneNode();
		vecWordMatrix.push_back(pSceneNode->GetTransform()->GetWorldMatrix());
	}
	(*pRenderParam) = vecWordMatrix;
	
}

void HrInstanceBatchHW::OnRenderEnd()
{
	HrInstanceBatch::OnRenderEnd();
}

