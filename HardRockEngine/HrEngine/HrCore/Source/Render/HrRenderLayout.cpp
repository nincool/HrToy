#include "Render/HrRenderLayout.h"
#include "Render/HrVertext.h"
#include "Render/HrHardwareBuffer.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_pVertextStruct = HrDirector::GetInstance().GetRenderFactory()->CreateVertext();
	m_pHardwareBuffer = HrDirector::GetInstance().GetRenderFactory()->CreatehardwareBuffer();

	m_topologyType = TT_TRIANGLELIST;
}

HrRenderLayout::~HrRenderLayout()
{
	SAFE_DELETE(m_pVertextStruct);
	SAFE_DELETE(m_pHardwareBuffer);
}

void HrRenderLayout::SetTopologyType(EnumTopologyType topologyType)
{
	m_topologyType = topologyType;
}

void HrRenderLayout::BindVertextBuffer(char* pBuffer
	, uint32 nBufferSize
	, IGraphicsBuffer::EnumHardwareBufferUsage usage
	, HrVertextElement* pVertexElementArr
	, uint32 nVertexElementLength)
{
	m_pHardwareBuffer->BindVertexStream(pBuffer, nBufferSize, usage);
	m_pVertextStruct->AddElementArray(pVertexElementArr, nVertexElementLength);
}

uint32 HrRenderLayout::GetVertextSize()
{
	return m_pVertextStruct->;
}

