#ifndef _HR_RECT_H_
#define _HR_RECT_H_

#include "HrMathPrerequisites.h"

namespace Hr
{
	class HrRect
	{
	public:
		HrRect();
		HrRect(float x, float y, float width, float height);
		HrRect(const HrRect& rt);

		HrRect& operator= (const HrRect& rt);
	public:
		void SetRect(float x, float y, float width, float height);
		
		float GetX() const;
		float GetY() const;
		float GetWidth() const;
		float GetHeight() const;

		bool Equals(const HrRect& rt) const;
		bool ContainsPoint(const Vector2& point);
	private:
		float m_fX;
		float m_fY;
		float m_fWidth;
		float m_fHeight;
	};
}


#endif


