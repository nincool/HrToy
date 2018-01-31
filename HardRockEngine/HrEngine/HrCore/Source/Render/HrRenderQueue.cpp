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

void HrRenderQueue::AddRenderable(const HrRenderablePtr& pRenderable)
{
	if (pRenderable)
	{
		if (m_mapRenderQueue.find(pRenderable) == m_mapRenderQueue.end())
		{
			m_mapRenderQueue.emplace(pRenderable, pRenderable->GetSceneNode());
		}
	}
}

const std::unordered_map<HrRenderablePtr, HrSceneNodePtr>& HrRenderQueue::GetRenderables()
{
	return m_mapRenderQueue;
}



