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

void Hr::HrVertext::AddElementArray(HrVertextElement* pVertexElementArr, uint32 nVertexElementLength)
{
	for (size_t i = 0; i < nVertexElementLength; ++i)
	{
		AddElement(pVertexElementArr[i]);
	}
}

void HrVertext::AddElement(HrVertextElement& usage)
{
	m_lisVertextElement.emplace_back(usage);
}

uint32 HrVertext::GetVertextSize()
{
	return m_nVertexSize;
}


