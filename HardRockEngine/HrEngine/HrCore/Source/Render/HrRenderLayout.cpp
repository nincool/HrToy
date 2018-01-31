#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrRenderFactory.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrRenderSystem.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_pVertex = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderFactory()->CreateVertex();
	m_pVertexBuffer = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderFactory()->CreateGraphicsBuffer();
	m_pIndexBuffer = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderFactory()->CreateGraphicsBuffer();

	m_topologyType = TT_TRIANGLELIST;
	m_indexBufferType = IT_16BIT;

	m_nVertices = 0;
	m_nIndices = 0;

	m_nIndexStartLocation = 0;
	m_nVertexStartLocation = 0;
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
	, std::vector<HrVertexElement>& vecVertexElement)
{
	m_pVertexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_VERTEXT);
	m_pVertex->AddElementArray(vecVertexElement);
	m_nVertices = nBufferSize / m_pVertex->GetVertexSize();
}

void HrRenderLayout::BindIndexBuffer(const char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, EnumIndexType indexType)
{
	m_indexBufferType = indexType;
	m_nIndices = nBufferSize / (indexType == IT_16BIT ? 2 : 4);
	m_pIndexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_INDEX);
}

uint32 HrRenderLayout::GetVertexSize()
{
	return m_pVertex->GetVertexSize();
}

EnumTopologyType HrRenderLayout::GetTopologyType()
{
	return m_topologyType;
}

bool HrRenderLayout::UseIndices()
{
	return m_pIndexBuffer->GetByteWidth();
}

void HrRenderLayout::SetIndexBufferType(EnumIndexType indexType)
{
	m_indexBufferType = indexType;
}

EnumIndexType HrRenderLayout::GetIndexBufferType()
{
	return m_indexBufferType;
}

uint32 HrRenderLayout::GetIndicesNum() const
{
	return m_nIndices;
}

uint32 HrRenderLayout::GetVerticesNum() const
{
	return m_nVertices;
}

void HrRenderLayout::SetStartVertexLocaltion(uint32 nStartLocation)
{
	m_nVertexStartLocation = nStartLocation;
}

uint32 HrRenderLayout::GetStartVertexLocaltion() const
{
	return m_nVertexStartLocation;
}

void HrRenderLayout::SetStartIndexLocation(uint32 nStartLocation)
{
	m_nIndexStartLocation = nStartLocation;
}

uint32 HrRenderLayout::GetStartIndexLocation() const
{
	return m_nIndexStartLocation;
}

