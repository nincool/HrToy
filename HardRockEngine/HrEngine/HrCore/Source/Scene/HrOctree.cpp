#include "Scene/HrOctree.h"
#include "Scene/HrOctNode.h"

using namespace Hr;

HrOctree::HrOctree()
{
	m_pRootNode = new HrOctNode(m_aabb, 1);
}

HrOctree::~HrOctree()
{
	SAFE_DELETE(m_pRootNode);
}

void HrOctree::InitOctree(const AABBox& aabb)
{
	
}

void HrOctree::InsertOctNode(const HrRenderablePtr& pRenderable)
{
	m_pRootNode->InsertChild(pRenderable, 16);
}

