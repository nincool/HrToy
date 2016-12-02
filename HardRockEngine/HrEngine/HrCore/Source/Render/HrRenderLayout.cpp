#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrRenderFactory.h"
#include "Kernel/HrDirector.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_pVertex = HrDirector::Instance()->GetRenderFactory()->CreateVertex();
	m_pHDVertexBuffer = HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();
	m_pHDIndexBuffer = HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();

	m_topologyType = TT_TRIANGLELIST;
	m_indexBufferType = IT_16BIT;

	m_nVertices = 0;
	m_nIndices = 0;
}

HrRenderLayout::~HrRenderLayout()
{
	SAFE_DELETE(m_pVertex);
	SAFE_DELETE(m_pHDVertexBuffer);
	SAFE_DELETE(m_pHDIndexBuffer);
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
	m_pHDVertexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_VERTEXT);
	m_pVertex->AddElementArray(vecVertexElement);
	m_nVertices = nBufferSize / m_pVertex->GetVertexSize();
}

void HrRenderLayout::BindIndexBuffer(const char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, EnumIndexType indexType)
{
	m_indexBufferType = indexType;
	m_nIndices = nBufferSize / (indexType == IT_16BIT ? 2 : 4);
	m_pHDIndexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_INDEX);
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
	return m_pHDIndexBuffer->GetByteWidth();
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



