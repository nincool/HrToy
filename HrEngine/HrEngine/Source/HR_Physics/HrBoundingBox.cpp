#include "HrBoundingBox.h"


using namespace HR;
CHrBoundingBox::CHrBoundingBox()
{
	m_vMin.x = CHrD3DUtil::INFINITYFLOAT;
	m_vMin.y = CHrD3DUtil::INFINITYFLOAT;
	m_vMin.z = CHrD3DUtil::INFINITYFLOAT;

	m_vMax.x = -CHrD3DUtil::INFINITYFLOAT;
	m_vMax.y = -CHrD3DUtil::INFINITYFLOAT;
	m_vMax.z = -CHrD3DUtil::INFINITYFLOAT;
}

CHrBoundingBox::~CHrBoundingBox()
{
}

bool CHrBoundingBox::IsPointInside(D3DXVECTOR3& point)
{
	return (point.x >= m_vMin.x && point.y >= m_vMin.y && point.z >= m_vMin.z &&
		point.x <= m_vMax.x && point.y <= m_vMax.y && point.z <= m_vMax.z);
}

