#include "Render/HrRenderLayout.h"
#include "Render/HrVertext.h"
#include "Render/HrHardwareBuffer.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"

using namespace Hr;

HrRenderLayout::HrRenderLayout()
{
	m_pVertextStruct = nullptr;
	m_pHardwareBuffer = nullptr;

	m_topologyType = TT_TRIANGLELIST;
}

HrRenderLayout::~HrRenderLayout()
{
	SAFE_DELETE(m_pVertextStruct);
	SAFE_DELETE(m_pHardwareBuffer);
}

void HrRenderLayout::BindVertextBuffer(IGraphicsBuffer * pGraphicsBuffer, HrVertext* pVertext)
{
	SAFE_DELETE(m_pHardwareBuffer);
	m_pHardwareBuffer = HrDirector::GetInstance().GetRenderFactory()->CreateHardwareBufferWithInstance(pGraphicsBuffer);
	
	if (!m_pVertextStruct)
	{
		m_pVertextStruct = HR_NEW HrVertext();
	}
	m_pVertextStruct->CopyFrom(pVertext);
}

uint32 HrRenderLayout::GetVertextSize()
{
	return 0;
}
