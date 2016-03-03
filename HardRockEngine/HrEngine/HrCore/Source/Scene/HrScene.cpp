#include "Scene/HrScene.h"
#include "HrDirector.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"


using namespace Hr;

HrScene::HrScene()
{
	//m_pShareSceneManager = HrDirector::GetInstance().
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
	
}

void HrScene::ClearSceneNode()
{
	m_pShareRootNode->RemoveChildren();
}

void HrScene::AddSceneNode(ISceneNode* pSceneNode)
{
	m_pShareRootNode->AddChild(pSceneNode);
}

void HrScene::Update()
{

}

void HrScene::FillRenderQueue(IRenderQueuePtr& pRenderQueue)
{
	//²éÕÒ¿ÉÊÓ
	m_pShareRootNode->FindVisibleRenderable(pRenderQueue);
}


