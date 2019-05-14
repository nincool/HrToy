
#include "Scene/HrOctNode.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderQueue.h"

using namespace Hr;

HrOctNode::HrOctNode(const AABBox& aabb, int nDepth, bool bLeafNode)
{
	m_aabb = aabb;
	m_nDepth = nDepth;
	m_bLeafNode = bLeafNode;
	m_bInitAABB = false;
	m_selfNV = HrMath::NV_UNKNOWN;
	m_arrChildren.assign(nullptr);
}

HrOctNode::~HrOctNode()
{

}

bool HrOctNode::IsLeafNode() const
{
	return m_bLeafNode;
}

void HrOctNode::SetAABB(const AABBox& aabb)
{
	m_aabb = aabb;
}

bool HrOctNode::DetectNodeVisible(const HrCameraPtr& pCamera, float fThreshold)
{
	if (m_selfNV == HrMath::NV_UNKNOWN)
	{
		if (fThreshold > 0)
		{
			if ((HrMath::OrthoArea(pCamera->GetForward(), m_aabb) > fThreshold)
				&& HrMath::PerspectiveArea(pCamera->GetEyePos(), pCamera->GetViewProjMatrix(), m_aabb) > fThreshold)
			{
				m_selfNV = HrMath::Map(pCamera->ViewFrustum().Intersect(m_aabb));
			}
			else
			{
				m_selfNV = HrMath::NV_NONE;
			}
		}
		else
		{
			m_selfNV = HrMath::Map(pCamera->ViewFrustum().Intersect(m_aabb));
		}
	}

	return m_selfNV != HrMath::NV_NONE;
}

bool HrOctNode::DetectDataVisible(const HrCameraPtr& pCamera, float fThreshold, const AABBox& dataAABB)
{
	if (!m_bLeafNode)
	{
		return false;
	}

	if (m_selfNV == HrMath::NV_FULL)
	{
		if (fThreshold > 0)
		{
			if ((HrMath::OrthoArea(pCamera->GetForward(), dataAABB) > fThreshold)
				&& HrMath::PerspectiveArea(pCamera->GetEyePos(), pCamera->GetViewProjMatrix(), dataAABB) > fThreshold)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	else if (m_selfNV == HrMath::NV_PARTIAL)
	{
		//判断是否包含
		auto dataNV = HrMath::Map(pCamera->ViewFrustum().Intersect(dataAABB));
		if (dataNV != HrMath::NV_NONE)
		{
			if (fThreshold > 0)
			{
				if ((HrMath::OrthoArea(pCamera->GetForward(), dataAABB) > fThreshold)
					&& HrMath::PerspectiveArea(pCamera->GetEyePos(), pCamera->GetViewProjMatrix(), dataAABB) > fThreshold)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

void HrOctNode::WalkTree(const HrCameraPtr& pCamera, HrSceneNode* pSceneNode, float fThreshold, int nMaxDepth)
{
	//先判断是否可见 
	//如果这个节点本身就不可见 
	//那么就不用初始化了 落在这个区域的物体也不可见
	if (!DetectNodeVisible(pCamera, fThreshold))
	{
		return;
	}

	// If this node doesn't have a data point yet assigned 
	// and it is a leaf, then we're done!
	if (m_nDepth == nMaxDepth)
	{
		if (DetectDataVisible(pCamera, fThreshold, pSceneNode->GetTransform()->GetWorldAABBox()))
		{
			if (pSceneNode->GetFrustumVisible() != HrMath::NV_FULL)
				pSceneNode->SetFrustumVisible(HrMath::NV_FULL);
		}
	}
	else
	{
		if (!m_bInitAABB)
		{
			InitChildrenNode(nMaxDepth);
		}

		const float3& parentCenter = m_aabb.Center();
		const AABBox& aabb = pSceneNode->GetTransform()->GetWorldAABBox();
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
				m_arrChildren[j]->WalkTree(pCamera, pSceneNode, fThreshold, nMaxDepth);
			}
		}
	}
}

void HrOctNode::InitChildrenNode(int nMaxDepth)
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
		if (!m_arrChildren[i])
			m_arrChildren[i] = new HrOctNode(AABBox(min, max), m_nDepth + 1, (nMaxDepth == (m_nDepth + 1)));
		else
			m_arrChildren[i]->SetAABB(AABBox(min, max));
	}
	m_bInitAABB = true;
}

void HrOctNode::ClearChildren()
{
	for (auto& iteChild : m_arrChildren)
	{
		if (iteChild)
			iteChild->ClearChildren();
	}

	m_selfNV = HrMath::NV_UNKNOWN;
	m_bInitAABB = false;
}

const AABBox& HrOctNode::GetAABB()
{
	return m_aabb;
}

