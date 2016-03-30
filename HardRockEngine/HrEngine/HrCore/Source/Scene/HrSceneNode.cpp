#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderTarget.h"
#include "Scene/HrCameraNode.h"
#include "HrDirector.h"
#include "HrLog.h"
#include <boost/cast.hpp>

using namespace Hr;

HrSceneNode::HrSceneNode() 
{
	m_nodeType = NT_NORMAL;
	m_pRenderable = nullptr;
	m_pParent = nullptr;
}

HrSceneNode::HrSceneNode(IRenderable* pRenderable) 
{
	m_pRenderable = pRenderable;
}

HrSceneNode::~HrSceneNode()
{
	SAFE_DELETE(m_pRenderable);
}

HrSceneNode::EnumNodeType HrSceneNode::GetNodeType()
{
	return m_nodeType;
}

HrSceneNode* HrSceneNode::GetParent()
{
	return m_pParent;
}

IRenderable* HrSceneNode::GetRenderable()
{
	return m_pRenderable;
}

void HrSceneNode::AddChild(HrSceneNode* pSceneNode)
{
	if (pSceneNode->GetParent() != nullptr)
	{
		HRERROR(_T("SceneNode AddChild Error! Already has parent"));
		return;
	}
	if (pSceneNode->GetNodeType() == NT_CAMERA)
	{
		HrCameraNode* pCameraNode = boost::polymorphic_downcast<HrCameraNode*>(pSceneNode);
		HrViewPort* pViewPort = pCameraNode->GetViewPort();
		HrDirector::GetInstance().GetRenderTarget()->AddViewPort(pViewPort);
	}

	m_vecChildNode.push_back(pSceneNode);
}

void HrSceneNode::FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue)
{
	if (m_pRenderable != nullptr)
	{
		pRenderQueue->AddRenderable(this);
	}
	for (auto& item : m_vecChildNode)
	{
		item->FindVisibleRenderable(pRenderQueue);
	}
}

void HrSceneNode::RemoveChildren()
{
	for (auto& item : m_vecChildNode)
	{
		HR_DELETE item;
	}
	m_vecChildNode.clear();
}

void HrSceneNode::UpdateNode(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pRenderable)
	{
		m_pRenderable->Update(renderFrameParameters);
	}
}

void HrSceneNode::SetPosition(const Vector3& v3Pos)
{
	m_v3LocalPosition = v3Pos;
}

void HrSceneNode::SetPosition(REAL x, REAL y, REAL z)
{
	Vector3 v(x, y, z);
	SetPosition(v);
}

const Vector3& HrSceneNode::GetPosition()
{
	return m_v3LocalPosition;
}




