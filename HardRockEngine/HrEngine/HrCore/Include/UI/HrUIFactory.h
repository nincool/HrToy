#ifndef _HR_UIFACTORY_H_
#define _HR_UIFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"


namespace Hr
{
	class HR_CORE_API HrUIFactory : public HrSingleTon<HrUIFactory>
	{
	public:
		HrUIFactory();
		~HrUIFactory();

		HrSceneNodePtr CreateUICanvasNode(const std::string& strName);

		HrSceneNodePtr CreateUISprite(const std::string& strFileName);
		HrSceneNodePtr CreateUIButton(const std::string& strNormalImage, const std::string& strSelectedImage = "", const std::string& strDisableImage = "");
	};
}

#endif
