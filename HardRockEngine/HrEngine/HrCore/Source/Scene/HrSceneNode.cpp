#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderTarget.h"
#include "Scene/HrCameraNode.h"
#include "Scene/HrTransform.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include <boost/cast.hpp>

using namespace Hr;

HrSceneNode::HrSceneNode() : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_nodeType = NT_NORMAL;
	m_pRenderable = nullptr;
	m_pParent = nullptr;

	m_pTransform = HR_NEW HrTransform(this);

	m_bDirtyTransform = false;
}

HrSceneNode::HrSceneNode(HrRenderable* pRenderable) : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	AttachRenderable(pRenderable);
}

HrSceneNode::~HrSceneNode()
{
	for (size_t i = 0; i < m_vecChildNode.size(); ++i)
	{
		SAFE_DELETE(m_vecChildNode[i]);
	}
	m_vecChildNode.clear();

	SAFE_DELETE(m_pTransform);
	SAFE_DELETE(m_pRenderable);
}

void HrSceneNode::AttachRenderable(HrRenderable* pRenderable)
{
	m_pRenderable = pRenderable;
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
		HrDirector::Instance()->GetRenderTarget()->AddViewPort(pViewPort);
	}

	m_vecChildNode.push_back(pSceneNode);
}

void HrSceneNode::FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue)
{
	if (m_pRenderable != nullptr && m_pRenderable->CanRender())
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
	for (size_t i = 0; i < m_vecChildNode.size(); ++i)
	{
		SAFE_DELETE(m_vecChildNode[i]);
	}
	m_vecChildNode.clear();
}

void HrSceneNode::UpdateNode()
{

}

void HrSceneNode::UpdateRenderParamData(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pRenderable)
	{
		m_pRenderable->UpdateRenderFrameParameters(renderFrameParameters);
	}
}

void HrSceneNode::DirtyTransform()
{
	m_bDirtyTransform = true;
}

