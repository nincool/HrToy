#include "Render/HrInstanceBatchHW.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Asset/HrMesh.h"
#include "Asset/HrStreamData.h"

using namespace Hr;

HrInstanceBatchHW::HrInstanceBatchHW()
{

}

HrInstanceBatchHW::~HrInstanceBatchHW()
{

}

void HrInstanceBatchHW::BuildVertices(const HrSubMeshPtr& pSubMesh)
{
	m_pBatchRenderLayout = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderFactory()->CreateRenderLayout();
	const HrRenderLayoutPtr& pBaseRenderLayout = pSubMesh->GetRenderLayout();
	m_pBatchRenderLayout->SetTopologyType(pBaseRenderLayout->GetTopologyType());


	const std::vector<HrVertexDataPtr>& vecBaseVertexStreams = pBaseRenderLayout->GetVertexStreams();
	for (size_t i = 0; i < vecBaseVertexStreams.size(); ++i)
	{
		const HrVertexDataPtr& pVertexData = vecBaseVertexStreams[i];
		pBaseRenderLayout->BindVertexBuffer(pVertexData->GetVertexBaseData()->GetBufferPoint()
			, pVertexData->GetVertexBaseData()->GetBufferSize()
			, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
			, pVertexData->GetVertex()->GetVertexElement());
	}

	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3, VEC_INSTANCE, 1));

	std::vector<float> vecInstanceData;
	vecInstanceData.reserve(HR_MAX_INSTANCE_NUM);
	for (size_t i = 0; i < vecInstanceData.size(); ++i)
	{
		vecInstanceData.push_back(static_cast<float>(i));
	}

	pBaseRenderLayout->BindVertexBuffer(reinterpret_cast<char*>(&vecInstanceData[0])
		, vecInstanceData.size() * sizeof(float)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vecVertexElement);
}


