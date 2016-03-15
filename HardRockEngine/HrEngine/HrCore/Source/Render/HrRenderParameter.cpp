#include "Render/HrRenderParameter.h"

using namespace Hr;

HrRenderParameter::HrRenderParameter()
{
	m_paramType = HrRenderParameter::RPT_UNKNOWN;
	m_nStartOffset = 0;
	m_dataType = HrRenderParameter::RPDT_FLOAT;
}

HrRenderParameter::~HrRenderParameter()
{

}


