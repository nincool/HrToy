#include "Render/HrRenderQueue.h"

using namespace Hr;

HrRenderQueue::~HrRenderQueue()
{

}

void HrRenderQueue::PrepareRenderQueue()
{
	m_mapRenderQueue.clear();
}

void HrRenderQueue::AddRenderable(ISceneNode* pSceneNode)
{
	IRenderable* pRenderable = pSceneNode->
}

