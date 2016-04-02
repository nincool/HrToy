#include "HrGeometryScene.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Asset/HrComponentFactory.h"
#include "HrCore/Include/Scene/HrSceneNode.h"
#include "HrCore/Include/Scene/HrCameraNode.h"


using namespace Hr;

HrGeometryScene::HrGeometryScene()
{

}

HrGeometryScene::~HrGeometryScene()
{

}

void HrGeometryScene::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();
}

void HrGeometryScene::CreateSceneElements()
{
	//Ìí¼ÓÉãÏñ»ú
	HrCameraNode* pCameraNode = HrComponentFactory::GetInstance().CreateCamera(0, 0, 640, 480, 1);
	AddSceneNode(pCameraNode);
	pCameraNode->Translate(Vector3(2.0f, 0, 0));

	HrSceneNode* pBox = HrGeometryFactory::GetInstance().CreateBox(10, 10, 10);
	AddSceneNode(pBox);
}

