#include "Render/HrVertex.h"

using namespace Hr;


//////////////////////////////////////////////////////////////////////////////////
// ElementVertex
//////////////////////////////////////////////////////////////////////////////////

size_t HrVertexElement::GetTypeSize()
{
	return GetTypeSize(m_elementType);
}

size_t HrVertexElement::GetTypeSize(EnumVertexElementType elementType)
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
// HrVertex
//////////////////////////////////////////////////////////////////////////////////

HrVertex::HrVertex()
{
	m_nVertexSize = 0;
}

HrVertex::~HrVertex()
{
}

void HrVertex::Clear()
{
	m_vecVertexElement.clear();
}

void HrVertex::AddElementArray(HrVertexElement* pVertexElementArr, uint32 nVertexElementLength)
{
	size_t nOffset = 0;
	for (size_t i = 0; i < nVertexElementLength; ++i)
	{
		pVertexElementArr[i].SetOffset(nOffset);
		AddElement(pVertexElementArr[i]);
		nOffset += pVertexElementArr[i].GetTypeSize();
	}
	m_nVertexSize = nOffset;
}

void HrVertex::AddElement(HrVertexElement& usage)
{
	m_vecVertexElement.emplace_back(usage);
}

uint32 HrVertex::GetVertexSize()
{
	return m_nVertexSize;
}

size_t HrVertex::GetVertexElementNum()
{
	return m_vecVertexElement.size();
}

const HrVertexElement& HrVertex::GetVertexElement(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecVertexElement.size());
	return m_vecVertexElement[nIndex];
}

