#include "UI/HrUIButton.h"

using namespace Hr;

HrUIButton::HrUIButton(const std::string& strNormalImage, const std::string& strSelectedImage /*= ""*/, const std::string& strDisableImage /*= ""*/)
{

}

HrUIButton::~HrUIButton()
{

}

void HrUIButton::LoadTextureNormal(const std::string& strNormalImage)
{
	m_strNormalImage = strNormalImage;
}

void HrUIButton::LoadTextureSelected(const std::string& strSelectedImage)
{
	m_strSelectedImage = strSelectedImage;

}

void HrUIButton::LoadTextureDisable(const std::string& strDisableIamge)
{
	m_strDisableImage = strDisableIamge;

}







