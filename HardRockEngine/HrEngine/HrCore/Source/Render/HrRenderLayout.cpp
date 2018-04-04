#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrRenderFactory.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrRenderSystem.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_topologyType = TT_TRIANGLELIST;
	m_indexBufferType = IT_16BIT;
	m_bStreamsDirty = true;
	m_nInstance = 1;
}

HrRenderLayout::~HrRenderLayout()
{
}

void HrRenderLayout::SetTopologyType(EnumTopologyType topologyType)
{
	m_topologyType = topologyType;
}

void HrRenderLayout::BindVertexBuffer(const char* pBuffer
	, uint64 nBufferSize
	, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
	, const std::vector<HrVertexElement>& vecVertexElement)
{
	HrVertexDataPtr pVertexData = HrMakeSharedPtr<HrVertexData>();
	pVertexData->GetVertex()->AddElementArray(vecVertexElement);
	pVertexData->BindVertexStream(pBuffer, nBufferSize, usage, 0, nBufferSize / pVertexData->GetVertex()->GetVertexSize());
	m_vecVertexStreams.emplace_back(pVertexData);
}

void HrRenderLayout::BindIndexBuffer(const char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, EnumIndexType indexType)
{
	//m_indexBufferType = indexType;
	//m_nIndices = nBufferSize / (indexType == IT_16BIT ? 2 : 4);
	//m_pIndexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_INDEX);
}

EnumTopologyType HrRenderLayout::GetTopologyType()
{
	return m_topologyType;
}

bool HrRenderLayout::UseIndices()
{
	return false;
}

void HrRenderLayout::SetIndexBufferType(EnumIndexType indexType)
{
	m_indexBufferType = indexType;
}

EnumIndexType HrRenderLayout::GetIndexBufferType()
{
	return m_indexBufferType;
}

size_t HrRenderLayout::GetVertexStreamSize()
{
	return m_vecVertexStreams.size();
}

void HrRenderLayout::Active()
{

}

uint32 HrRenderLayout::GetVerticesNum()
{
	return m_vecVertexStreams[0]->GetVertexCount();
}

const std::vector<HrVertexDataPtr>& HrRenderLayout::GetVertexStreams()
{
	return m_vecVertexStreams;
}

uint32 HrRenderLayout::GetNextVertexSemanticIndex(EnumVertexElementSemantic semantic)
{
	uint32 nNexIndex = 0;
	for (size_t i = 0; i < m_vecVertexStreams.size(); ++i)
	{
		const std::vector<HrVertexElement>& vecElement = m_vecVertexStreams[i]->GetVertex()->GetVertexElement();
		for (auto& ele : vecElement)
		{
			if (ele.m_elementSemantic == semantic)
			{
				++nNexIndex;
			}
		}
	}

	return nNexIndex;
}

uint32 HrRenderLayout::GetInstanceNum()
{
	return m_nInstance;
}

void HrRenderLayout::SetInstanceNum(uint32 nInstance)
{
	m_nInstance = nInstance;
}

