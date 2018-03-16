#include "Render/HrRenderQueue.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRenderable.h"

using namespace Hr;

HrRenderQueue::~HrRenderQueue()
{

}

void HrRenderQueue::PrepareRenderQueue()
{
	m_vecSceneNodes.clear();
}

void HrRenderQueue::AddRenderable(const HrSceneNodePtr& pSceneNode)
{
	m_vecSceneNodes.push_back(pSceneNode);
}

const std::vector<HrSceneNodePtr>& HrRenderQueue::GetRenderables()
{
	return m_vecSceneNodes;
}



