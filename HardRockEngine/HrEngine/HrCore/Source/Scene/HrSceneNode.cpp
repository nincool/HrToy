#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderTarget.h"
#include "Scene/HrEntityNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneManager.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrSceneNode::HrSceneNode() : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_bEnable = true;

	m_nodeType = NT_NORMAL;
	m_pRenderable = nullptr;
	m_pParent = nullptr;
	m_bRunning = false;

	m_pTransform = HR_NEW HrTransform(this);

	m_bDirtyTransform = false;
}

HrSceneNode::HrSceneNode(HrRenderable* pRenderable) : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_bEnable = true;

	m_nodeType = NT_NORMAL;
	m_pRenderable = nullptr;
	m_pParent = nullptr;
	m_bRunning = false;

	m_pTransform = HR_NEW HrTransform(this);

	m_bDirtyTransform = false;

	AttachRenderable(pRenderable);
}

HrSceneNode::HrSceneNode(const std::string& strName, HrRenderable* pRenderable) 
	: HrIDObject(HrID::GenerateID<HrSceneNode>()), m_strName(strName)
{
	m_bEnable = true;

	m_nodeType = NT_NORMAL;
	m_pRenderable = nullptr;
	m_pParent = nullptr;
	m_bRunning = false;

	m_pTransform = HR_NEW HrTransform(this);

	m_bDirtyTransform = false;

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

void HrSceneNode::SetName(const std::string& strName)
{
	m_strName = strName;
}

const std::string& HrSceneNode::GetName() const
{
	return m_strName;
}

void HrSceneNode::AttachRenderable(HrRenderable* pRenderable)
{
	m_pRenderable = pRenderable;
	m_pRenderable->AttachSceneNode(this);
}

void HrSceneNode::AddChild(HrSceneNode* pSceneNode)
{
	if (pSceneNode->GetParent() != nullptr)
	{
		HRERROR(_T("SceneNode AddChild Error! Already has parent"));
		return;
	}

	pSceneNode->SetParent(this);
	if (IsRunning())
	{
		pSceneNode->OnEnter();
	}

	m_vecChildNode.push_back(pSceneNode);
}

void HrSceneNode::OnEnter()
{
	m_bRunning = true;
	for (auto& itemChild : m_vecChildNode)
	{
		itemChild->OnEnter();
	}
}

void HrSceneNode::OnEnterDidFinish()
{
}

void HrSceneNode::OnExist()
{
	m_bRunning = false;
	for (auto& itemChild : m_vecChildNode)
	{
		itemChild->OnExist();
	}
}

void HrSceneNode::FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue)
{
	if (this->m_bEnable)
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
}

void HrSceneNode::RemoveChildren()
{
	for (size_t i = 0; i < m_vecChildNode.size(); ++i)
	{
		m_vecChildNode[i]->OnExist();
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
	for (auto& itemChild : m_vecChildNode)
	{
		itemChild->GetTransform()->DirtyTransform();
	}
}

bool HrSceneNode::IsRunning() const
{
	return m_bRunning;
}

void HrSceneNode::SetParent(HrSceneNode* pParent)
{
	BOOST_ASSERT(pParent);
	if (pParent->IsRunning())
	{
		m_bRunning = true;
	}
	m_pParent = pParent;
}

HrSceneNode* HrSceneNode::GetParent() const
{
	return m_pParent;
}

HrRenderable* HrSceneNode::GetRenderable() const
{
	return m_pRenderable;
}

HrTransform* HrSceneNode::GetTransform() const
{
	return m_pTransform;
}

HrSceneNode* HrSceneNode::GetChildByName(const std::string& strName) const
{
	for (auto& item : m_vecChildNode)
	{
		if (item->m_strName == strName)
		{
			return item;
		}
	}
	return nullptr;
}

HrSceneNode* HrSceneNode::GetNodeByNameFromHierarchy(const std::string& strName)
{
	if (this->m_strName == strName)
	{
		return this;
	}
	else
	{
		for (auto& itemChild : m_vecChildNode)
		{
			HrSceneNode* pResult = itemChild->GetNodeByNameFromHierarchy(strName);
			if (pResult != nullptr)
			{
				return pResult;
			}
		}

		return nullptr;
	}
}

void HrSceneNode::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

bool HrSceneNode::GetEnable() const
{
	return m_bEnable;
}
