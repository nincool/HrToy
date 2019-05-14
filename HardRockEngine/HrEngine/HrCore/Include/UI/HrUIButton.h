#ifndef _HR_UIBUTTON_H_
#define _HR_UIBUTTON_H_

#include "HrCore/Include/UI/HrUIWidget.h"


namespace Hr
{
	class HR_CORE_API HrUIButton : public HrUIWidget
	{
	public:
		HrUIButton(const std::string& strNormalImage, const std::string& strSelectedImage = "", const std::string& strDisableImage = "");
		virtual ~HrUIButton();

	protected:
		void LoadTextureNormal(const std::string& strNormalImage);
		void LoadTextureSelected(const std::string& strSelectedImage);
		void LoadTextureDisable(const std::string& strDisableIamge);
	protected:
		std::string m_strNormalImage;
		std::string m_strSelectedImage;
		std::string m_strDisableImage;

		HrTexturePtr m_pTextureNormal;
		HrTexturePtr m_pTextureSelected;
		HrTexturePtr m_pTextureDisable;
	};
}

#endif

