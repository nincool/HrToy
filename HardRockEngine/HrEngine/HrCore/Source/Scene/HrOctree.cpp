#include "Scene/HrOctree.h"
#include "Scene/HrOctNode.h"

using namespace Hr;

HrOctree::HrOctree()
{
	m_pRootNode = new HrOctNode(m_aabb, 1);
	m_fThreshold = 0.0f;
}

HrOctree::~HrOctree()
{
	SAFE_DELETE(m_pRootNode);
}

void HrOctree::InitOctree(const AABBox& aabb)
{
	m_pRootNode->SetAABB(aabb);
}

void HrOctree::Clear()
{
	m_pRootNode->ClearChildren();
}

const AABBox& HrOctree::GetAABB()
{
	return m_pRootNode->GetAABB();
}

void HrOctree::WalkTree(const HrCameraPtr& pCamera, const HrSceneNodePtr& pSceneNode)
{
	m_pRootNode->WalkTree(pCamera, pSceneNode, m_fThreshold, m_sc_nMaxDepth);
}

