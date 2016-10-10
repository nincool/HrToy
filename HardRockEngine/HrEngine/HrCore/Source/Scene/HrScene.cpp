#include "Scene/HrScene.h"
#include "HrDirector.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrScene::HrScene()
{
	m_pRootNode = MakeSharedPtr<HrSceneNode>();
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
	m_pRootNode->RemoveChildren();
}

void HrScene::AddSceneNode(HrSceneNode* pSceneNode)
{
	m_pRootNode->AddChild(pSceneNode);
}

void HrScene::Update()
{

}

void HrScene::FillRenderQueue(HrRenderQueuePtr& pRenderQueue)
{
	//²éÕÒ¿ÉÊÓ
	m_pRootNode->FindVisibleRenderable(pRenderQueue);
}


