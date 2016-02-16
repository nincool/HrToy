#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "HrLog.h"

using namespace Hr;

HrSceneNode::HrSceneNode() 
{
	m_pParent = nullptr;
}

HrSceneNode::HrSceneNode(IRenderable* pRenderable) 
{
	m_pRenderable = pRenderable;
}

HrSceneNode::~HrSceneNode()
{

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

}

