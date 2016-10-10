#include "Render/HrRenderQueue.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRenderable.h"

using namespace Hr;

HrRenderQueue::~HrRenderQueue()
{

}

void HrRenderQueue::PrepareRenderQueue()
{
	m_mapRenderQueue.clear();
}

void HrRenderQueue::AddRenderable(HrSceneNode* pSceneNode)
{
	HrRenderable* pRenderable = pSceneNode->GetRenderable();
	if (m_mapRenderQueue.find(pRenderable) == m_mapRenderQueue.end())
	{
		m_mapRenderQueue.emplace(pRenderable, pSceneNode);
	}
}

std::unordered_map<HrRenderable*, HrSceneNode*>& HrRenderQueue::GetRenderables()
{
	return m_mapRenderQueue;
}



