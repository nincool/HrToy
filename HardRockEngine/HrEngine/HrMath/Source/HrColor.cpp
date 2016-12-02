#include "HrColor.h"

using namespace Hr;

HrColor HrColor::Black(0.0f, 0.0f, 0.0f, 1.0f);
HrColor HrColor::White(1.0f, 1.0f, 1.0f, 1.0f);
HrColor HrColor::Red(1.0f, 0.0f, 0.0f, 1.0f);
HrColor HrColor::Green(1.0f, 1.0f, 0.0f, 1.0f);
HrColor HrColor::Blue(0.0f, 0.0f, 1.0f, 1.0f);
HrColor HrColor::Yellow(1.0f, 1.0f, 0.0f, 1.0f);
HrColor HrColor::Cyan(0.0f, 1.0f, 1.0f, 1.0f);
HrColor HrColor::Magenta(1.0f, 0.0f, 1.0f, 1.0f);
HrColor HrColor::Silver(0.75f, 0.75f, 0.75f, 1.0f);

HrColor::HrColor() :Color()
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

float4 HrColor::Value()
{
	return float4(r(), g(), b(), a());
}

