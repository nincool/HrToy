#include "Scene/HrScene.h"
#include "HrDirector.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrScene::HrScene()
{
	m_pShareRootNode = MakeSharedPtr<HrSceneNode>();
}

HrScene::~HrScene()
{
}

void HrScene::OnEnter()
{
}

void HrScene::OnEnterDidFinish()
{
}

void HrScene::OnExit()
{
	ClearSceneNode();
}

void HrScene::ClearSceneNode()
{
	m_pShareRootNode->RemoveChildren();
}

void HrScene::AddSceneNode(HrSceneNode* pSceneNode)
{
	m_pShareRootNode->AddChild(pSceneNode);
}

void HrScene::Update()
{

}

void HrScene::FillRenderQueue(HrRenderQueuePtr& pRenderQueue)
{
	//²éÕÒ¿ÉÊÓ
	m_pShareRootNode->FindVisibleRenderable(pRenderQueue);
}


