#include "HrColor.h"

using namespace Hr;

HrColor HrColor::Black(0.0f, 0.0f, 0.0f, 1.0f);
HrColor HrColor::White(1.0f, 1.0f, 1.0f, 1.0f);
HrColor HrColor::Red(1.0f, 0.0f, 0.0f, 1.0f);
HrColor HrColor::Green(0.0f, 1.0f, 0.0f, 1.0f);
HrColor HrColor::Blue(0.0f, 0.0f, 1.0f, 1.0f);
HrColor HrColor::Yellow(1.0f, 1.0f, 0.0f, 1.0f);
HrColor HrColor::Cyan(0.0f, 1.0f, 1.0f, 1.0f);
HrColor HrColor::Magenta(1.0f, 0.0f, 1.0f, 1.0f);
HrColor HrColor::Silver(0.75f, 0.75f, 0.75f, 1.0f);

HrColor::HrColor() :Color()
{
}

HrColor::HrColor(const HrColor& color) : KlayGE::Color(color)
{
}

HrColor::HrColor(HrColor&& color):KlayGE::Color(color)
{
}

HrColor::HrColor(const float* rhs):Color(rhs)
{
}

HrColor::HrColor(const float& rhs):Color(rhs)
{
}

HrColor::HrColor(float&& rhs):Color(rhs)
{
}

HrColor::HrColor(float r, float g, float b, float a):Color(r,g,b,a)
{
}

HrColor::HrColor(uint32 dw):Color(dw)
{
}

float4 HrColor::Value() const
{
	return float4(r(), g(), b(), a());
}

HrColor& HrColor::operator+=(HrColor const & rhs) 
{
	col_ += rhs.col_;
	return *this;
}

HrColor& HrColor::operator-=(HrColor const & rhs) 
{
	col_ -= rhs.col_;
	return *this;
}

HrColor& HrColor::operator*=(float rhs) 
{
	col_ *= rhs;
	return *this;
}

HrColor& HrColor::operator*=(HrColor const & rhs) 
{
	return HrColor(col_[0] * rhs[0], col_[1] * rhs[1], col_[2] * rhs[2], col_[3] * rhs[3]);
}

HrColor& HrColor::operator/=(float rhs) 
{
	col_ /= rhs;
	return *this;
}

HrColor& HrColor::operator=(HrColor const & rhs) 
{
	if (this != &rhs)
	{
		col_ = rhs.col_;
	}
	return *this;
}

HrColor& HrColor::operator=(HrColor&& rhs) 
{
	if (this != &rhs)
	{
		col_ = rhs.col_;
	}
	return *this;
}


HrColor const HrColor::operator+() const 
{
	return *this;
}

HrColor const HrColor::operator-() const 
{
	return HrColor(-this->r(), -this->g(), -this->b(), -this->a());
}

bool Hr::HrColor::operator==(HrColor const & rhs) const
{
	return col_ == rhs.col_;
}
