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
	IRenderable* pRenderable = pSceneNode->GetRenderable();
	if (m_mapRenderQueue.find(pRenderable) == m_mapRenderQueue.end())
	{
		m_mapRenderQueue.emplace(pRenderable, pSceneNode);
	}
}

std::unordered_map<IRenderable*, HrSceneNode*>& Hr::HrRenderQueue::GetRenderables()
{
	return m_mapRenderQueue;
}



