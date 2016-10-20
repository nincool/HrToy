#include "HrGeometryScene.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Scene/HrSceneNode.h"
#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Asset/HrComponentFactory.h"
#include "HrCore/Include/HrDirector.h"

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
	//��������
	HrCameraNode* pCameraNode = HrDirector::Instance()->GetComponentFactory()->CreateCamera(0, 0, 640, 480, 1);
	AddSceneNode(pCameraNode);
	
	//������������
	pCameraNode->Translate(Vector3(0, 0, 0));

	HrSceneNode* pBox = HrDirector::Instance()->GetComponentFactory()->CreateBox();
	AddSceneNode(pBox);
}

