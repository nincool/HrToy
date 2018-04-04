#include "Render/HrRenderQueue.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRenderable.h"

using namespace Hr;

HrRenderQueue::~HrRenderQueue()
{

}

void HrRenderQueue::PrepareRenderQueue()
{
	m_vecRenderables.clear();
}

void HrRenderQueue::AddRenderable(const HrRenderablePtr& pRenderable)
{
	m_vecRenderables.push_back(pRenderable);
}

const std::vector<HrRenderablePtr>& HrRenderQueue::GetRenderables()
{
	return m_vecRenderables;
}

