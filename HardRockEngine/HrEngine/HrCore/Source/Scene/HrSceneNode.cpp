#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "HrLog.h"

using namespace Hr;

HrSceneNode::HrSceneNode() 
{
	m_pRenderable = nullptr;
	m_pParent = nullptr;
}

HrSceneNode::HrSceneNode(IRenderable* pRenderable) 
{
	m_pRenderable = pRenderable;
}

HrSceneNode::~HrSceneNode()
{
	SAFE_DELETE(m_pRenderable);
}

ISceneNode* HrSceneNode::GetParent()
{
	return m_pParent;
}

IRenderable* HrSceneNode::GetRenderable()
{
	return m_pRenderable;
}

void HrSceneNode::AddChild(ISceneNode* pSceneNode)
{
	if (pSceneNode->GetParent() != nullptr)
	{
		HRERROR(_T("SceneNode AddChild Error! Already has parent"));
		return;
	}
	m_vecChildNode.push_back(pSceneNode);
}

void HrSceneNode::FindVisibleRenderable(IRenderQueuePtr& pRenderQueue)
{
	if (m_pRenderable != nullptr)
	{
		pRenderQueue->AddRenderable(this);
	}
	for (auto& item : m_vecChildNode)
	{
		item->FindVisibleRenderable(pRenderQueue);
	}
}

void HrSceneNode::RemoveChildren()
{
	for (auto& item : m_vecChildNode)
	{
		HR_DELETE item;
	}
	m_vecChildNode.clear();
}

