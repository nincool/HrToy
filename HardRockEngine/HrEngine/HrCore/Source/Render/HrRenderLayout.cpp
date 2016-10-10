#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrHardwareBuffer.h"
#include "Render/HrRenderFactory.h"
#include "HrDirector.h"

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

void HrRenderLayout::BindVertexBuffer(char* pBuffer
	, uint32 nBufferSize
	, HrGraphicsBuffer::EnumHardwareBufferUsage usage
	, HrVertexElement* pVertexElementArr
	, uint32 nVertexElementLength)
{
	m_pHDVertexBuffer->BindStream(pBuffer, nBufferSize, usage, HrGraphicsBuffer::HBB_VERTEXT);
	m_pVertex->AddElementArray(pVertexElementArr, nVertexElementLength);
}

void HrRenderLayout::BindIndexBuffer(char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumHardwareBufferUsage usage, EnumIndexType indexType)
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

void HrRenderLayout::SetIndicesNum(uint32 nIndicesNum)
{
	m_nIndices = nIndicesNum;
}

uint32 HrRenderLayout::GetIndicesNum()
{
	return m_nIndices;
}

