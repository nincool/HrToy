#include "Render/HrVertext.h"

using namespace Hr;

HrVertext::HrVertext()
{
	m_nVertexSize = 0;
}

HrVertext::~HrVertext()
{
}

void HrVertext::Clear()
{
	m_lisVertextElement.clear();
}

void HrVertext::CopyFrom(HrVertext* pVertext)
{
	m_lisVertextElement = pVertext->m_lisVertextElement;
}

void HrVertext::AddElement(HrVertextElement::EnumVertextElementUsage usage)
{
	m_lisVertextElement.emplace_back(usage);
}


