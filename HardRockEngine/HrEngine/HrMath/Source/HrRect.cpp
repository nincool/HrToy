#include "HrRect.h"
#include "HrMathCom.h"

using namespace Hr;

HrRect::HrRect()
	:m_fX(0), m_fY(0), m_fWidth(0), m_fHeight(0)
{
}

HrRect::HrRect(float x, float y, float width, float height)
	:m_fX(x), m_fY(y), m_fWidth(width), m_fHeight(height)
{
}

HrRect::HrRect(const HrRect& rt)
{
	m_fX = rt.m_fX;
	m_fY = rt.m_fY;
	m_fWidth = rt.m_fWidth;
	m_fHeight = rt.m_fHeight;
}

HrRect& HrRect::operator=(const HrRect& rt)
{
	m_fX = rt.m_fX;
	m_fY = rt.m_fY;
	m_fWidth = rt.m_fWidth;
	m_fHeight = rt.m_fHeight;

	return *this;
}

void HrRect::SetRect(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;
	m_fWidth = width;
	m_fHeight = height;
}

float HrRect::GetX() const
{
	return m_fX;
}

float HrRect::GetY() const
{
	return m_fY;
}

float HrRect::GetWidth() const
{
	return m_fWidth;
}

float HrRect::GetHeight() const
{
	return m_fHeight;
}

bool HrRect::Equals(const HrRect& rt) const
{
	bool rt1 = std::abs(m_fX - rt.m_fX) < HrMath::EPSILON;
	bool rt2 = std::abs(m_fY - rt.m_fY) < HrMath::EPSILON;
	bool rt3 = std::abs(m_fWidth - rt.m_fWidth) < HrMath::EPSILON;
	bool rt4 = std::abs(m_fHeight - rt.m_fHeight) < HrMath::EPSILON;

	return rt1 && rt2 && rt3 && rt4;
}

bool HrRect::ContainsPoint(const Vector2& point)
{
	if (point.x() >= m_fX && point.x() <= (m_fX + m_fWidth)
		&& point.y() >= m_fY && point.y() <= (m_fY + m_fHeight))
	{
		return true;
	}

	return false;
}

