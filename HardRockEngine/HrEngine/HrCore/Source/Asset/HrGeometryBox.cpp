#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Render/HrRenderLayout.h"

using namespace Hr;

HrGeometryBox::HrGeometryBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	m_nLength = nLength;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

HrGeometryBox::~HrGeometryBox()
{

}

void HrGeometryBox::InitRenderLayout()
{
	//m_pRenderLayout->SetTopologyType(HrRenderLayout::TT_TRIANGLELIST);
}

