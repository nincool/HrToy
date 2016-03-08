#include "HrGeometryScene.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Scene/HrSceneNode.h"

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
	HrSceneNode* pBox = HrGeometryFactory::GetInstance().Create2DTriangle();
	AddSceneNode(pBox);
}
