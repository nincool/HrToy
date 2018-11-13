#include "Scene/HrOctNode.h"
#include "Render/HrRenderable.h"

using namespace Hr;

HrOctNode::HrOctNode(const AABBox& aabb, int nDepth)
{
	m_aabb = aabb;
	m_nDepth = nDepth;
}

HrOctNode::~HrOctNode()
{

}

bool HrOctNode::IsLeafNode() const
{
	return m_vecChildren.empty();
}

void HrOctNode::InsertChild(const HrRenderablePtr& pRenderable, int nMaxDepth)
{
	// If this node doesn't have a data point yet assigned 
	// and it is a leaf, then we're done!
	if (m_nDepth == nMaxDepth)
	{
		m_vecDatas.push_back(pRenderable);
	}
	else
	{
		if (m_vecChildren.empty())
		{
			CreateChildren();
		}
		const float3& parentCenter = m_aabb.Center();
		const AABBox& aabb = pRenderable->GetAABBox();
		int mark[6];
		mark[0] = aabb.Min().x() >= parentCenter.x() ? 1 : 0;
		mark[1] = aabb.Min().y() >= parentCenter.y() ? 2 : 0;
		mark[2] = aabb.Min().z() >= parentCenter.z() ? 4 : 0;
		mark[3] = aabb.Max().x() >= parentCenter.x() ? 1 : 0;
		mark[4] = aabb.Max().y() >= parentCenter.y() ? 2 : 0;
		mark[5] = aabb.Max().z() >= parentCenter.z() ? 4 : 0;
		for (int j = 0; j < 8; ++j)
		{
			if (j == ((j & 1) ? mark[3] : mark[0])
				+ ((j & 2) ? mark[4] : mark[1])
				+ ((j & 4) ? mark[5] : mark[2]))
			{
				m_vecChildren[j]->InsertChild(pRenderable, nMaxDepth);
			}
		}
	}
}

void HrOctNode::CreateChildren()
{

	/**
		    6        7
		2       3
		    4        5
		0       1
	**/
	// Split the current node and create new empty trees for each
	// child octant.
	float3 parentCenter = m_aabb.Center();
	for (size_t i = 0; i < 8; ++i)
	{
		// Compute new bounding box for this child
		float3 min((i & 1) ? parentCenter.x() : m_aabb.Min().x(),
			(i & 2) ? parentCenter.y() : m_aabb.Min().y(),
			(i & 4) ? parentCenter.z() : m_aabb.Min().z());

		float3 max((i & 1) ? m_aabb.Max().x() : parentCenter.x(),
			(i & 2) ? m_aabb.Max().y() : parentCenter.y(),
			(i & 4) ? m_aabb.Max().z() : parentCenter.z());
		m_vecChildren.push_back(new HrOctNode(AABBox(min, max), m_nDepth + 1));
	}
}




