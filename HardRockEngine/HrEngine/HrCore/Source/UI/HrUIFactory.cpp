#include "UI/HrUIFactory.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"
#include "UI/HrUISprite.h"
#include "UI/HrUIButton.h"

using namespace Hr;

HrUIFactory::HrUIFactory()
{
}

HrUIFactory::~HrUIFactory()
{
}

HrSceneNodePtr HrUIFactory::CreateUICanvasNode(const std::string& strName)
{
	HrSceneNodePtr pUICanvasNode = HrMakeSharedPtr<HrSceneNode>(strName);
	HrCameraComponentPtr pCameraCom = pUICanvasNode->GetSceneObject()->AddComponent<HrCameraComponet>();
	pCameraCom->SetCameraType(HrCamera::CT_OTHOGRAPHIC);
	pUICanvasNode->GetSceneObject()->AddComponent<HrUICanvasComponent>();
	
	return pUICanvasNode;
}

HrSceneNodePtr HrUIFactory::CreateUISprite(const std::string& strFileName)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrUIComponentPtr pUICom = pSceneNode->GetSceneObject()->AddComponent<HrUIComponent>();
	HrUISpritePtr pSprite = HrMakeSharedPtr<HrUISprite>(strFileName);
	pUICom->SetUI(pSprite);

	return pSceneNode;
}

HrSceneNodePtr HrUIFactory::CreateUIButton(const std::string& strNormalImage
	, const std::string& strSelectedImage /*= ""*/
	, const std::string& strDisableImage /*= ""*/)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrUIComponentPtr pUICom = pSceneNode->GetSceneObject()->AddComponent<HrUIComponent>();
	HrUIButtonPtr pUIButton = HrMakeSharedPtr<HrUIButton>(strNormalImage, strSelectedImage, strDisableImage);

	return nullptr;
}

