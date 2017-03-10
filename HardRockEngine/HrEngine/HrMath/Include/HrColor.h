#ifndef _HR_COLOR_H_
#define _HR_COLOR_H_

#include "HrMathPrerequisites.h"

namespace Hr
{
	class HrColor : public KlayGE::Color
	{
	public:
		HrColor();
		HrColor(const HrColor& color);
		HrColor(HrColor&& color);
		explicit HrColor(const float* rhs);
		HrColor(const float& rhs);
		HrColor(float&& rhs);
		HrColor(float r, float g, float b, float a);
		explicit HrColor(uint32 dw);

		// 赋值操作符
		HrColor& operator+=(HrColor const & rhs);
		HrColor& operator-=(HrColor const & rhs);
		HrColor& operator*=(float rhs);
		HrColor& operator*=(HrColor const & rhs);
		HrColor& operator/=(float rhs);

		HrColor& operator=(HrColor const & rhs);
		HrColor& operator=(HrColor&& rhs);

		// 一元操作符
		HrColor const operator+() const;
		HrColor const operator-() const;

		bool operator==(HrColor const & rhs) const;


		float4 Value() const;
	public:
		static HrColor Black;
		static HrColor White;
		static HrColor Red;
		static HrColor Green;
		static HrColor Blue;
		static HrColor Yellow;
		static HrColor Cyan;
		static HrColor Magenta;
		static HrColor Silver;

	};
}


#endif


