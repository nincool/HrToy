#include "Render/HrVertext.h"

using namespace Hr;


//////////////////////////////////////////////////////////////////////////////////
// ElementVertext
//////////////////////////////////////////////////////////////////////////////////

size_t HrVertextElement::GetTypeSize()
{
	return GetTypeSize(m_elementType);
}

size_t HrVertextElement::GetTypeSize(EnumVertexElementType elementType)
{
	switch (elementType)
	{
	case VET_COLOUR:
	case VET_COLOUR_ABGR:
	case VET_COLOUR_ARGB:
		return sizeof(uint32);
	case VET_FLOAT1:
		return sizeof(float);
	case VET_FLOAT2:
		return sizeof(float) * 2;
	case VET_FLOAT3:
		return sizeof(float) * 3;
	case VET_FLOAT4:
		return sizeof(float) * 4;
	case VET_DOUBLE1:
		return sizeof(double);
	case VET_DOUBLE2:
		return sizeof(double) * 2;
	case VET_DOUBLE3:
		return sizeof(double) * 3;
	case VET_DOUBLE4:
		return sizeof(double) * 4;
	case VET_SHORT1:
		return sizeof(short);
	case VET_SHORT2:
		return sizeof(short) * 2;
	case VET_SHORT3:
		return sizeof(short) * 3;
	case VET_SHORT4:
		return sizeof(short) * 4;
	case VET_USHORT1:
		return sizeof(unsigned short);
	case VET_USHORT2:
		return sizeof(unsigned short) * 2;
	case VET_USHORT3:
		return sizeof(unsigned short) * 3;
	case VET_USHORT4:
		return sizeof(unsigned short) * 4;
	case VET_INT1:
		return sizeof(int);
	case VET_INT2:
		return sizeof(int) * 2;
	case VET_INT3:
		return sizeof(int) * 3;
	case VET_INT4:
		return sizeof(int) * 4;
	case VET_UINT1:
		return sizeof(unsigned int);
	case VET_UINT2:
		return sizeof(unsigned int) * 2;
	case VET_UINT3:
		return sizeof(unsigned int) * 3;
	case VET_UINT4:
		return sizeof(unsigned int) * 4;
	case VET_UBYTE4:
		return sizeof(unsigned char) * 4;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// HrVertext
//////////////////////////////////////////////////////////////////////////////////

HrVertext::HrVertext()
{
	m_nVertexSize = 0;
}

HrVertext::~HrVertext()
{
}

void HrVertext::Clear()
{
	m_vecVertextElement.clear();
}

void HrVertext::AddElementArray(HrVertextElement* pVertexElementArr, uint32 nVertexElementLength)
{
	size_t nOffset = 0;
	for (size_t i = 0; i < nVertexElementLength; ++i)
	{
		pVertexElementArr->SetOffset(nOffset);
		AddElement(pVertexElementArr[i]);
		nOffset += pVertexElementArr[i].GetTypeSize();
	}
	m_nVertexSize = nOffset;
}

void HrVertext::AddElement(HrVertextElement& usage)
{
	m_vecVertextElement.emplace_back(usage);
}

uint32 HrVertext::GetVertextSize()
{
	return m_nVertexSize;
}

size_t HrVertext::GetVertextElementNum()
{
	return m_vecVertextElement.size();
}

const HrVertextElement& HrVertext::GetVertextElement(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecVertextElement.size());
	return m_vecVertextElement[nIndex];
}

