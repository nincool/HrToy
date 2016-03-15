#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Render/HrHardwareBuffer.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_pVertex = HrDirector::GetInstance().GetRenderFactory()->CreateVertex();
	m_pHDVertexBuffer = HrDirector::GetInstance().GetRenderFactory()->CreatehardwareBuffer();
	m_pHDIndexBuffer = HrDirector::GetInstance().GetRenderFactory()->CreatehardwareBuffer();

	m_topologyType = TT_TRIANGLELIST;
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
	, IGraphicsBuffer::EnumHardwareBufferUsage usage
	, HrVertexElement* pVertexElementArr
	, uint32 nVertexElementLength)
{
	m_pHDVertexBuffer->BindStream(pBuffer, nBufferSize, usage, IGraphicsBuffer::HBB_VERTEXT);
	m_pVertex->AddElementArray(pVertexElementArr, nVertexElementLength);
}

void HrRenderLayout::BindIndexBuffer(char* pBuffer, uint32 nBufferSize, IGraphicsBuffer::EnumHardwareBufferUsage usage)
{
	m_pHDIndexBuffer->BindStream(pBuffer, nBufferSize, usage, IGraphicsBuffer::HBB_INDEX);
}

uint32 HrRenderLayout::GetVertexSize()
{
	return m_pVertex->GetVertexSize();
}

IRenderLayout::EnumTopologyType HrRenderLayout::GetTopologyType()
{
	return m_topologyType;
}

bool HrRenderLayout::UseIndices()
{
	return m_pHDIndexBuffer->GetByteWidth();
}

