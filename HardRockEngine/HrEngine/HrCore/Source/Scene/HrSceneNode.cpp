#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderTarget.h"
#include "Scene/HrEntityNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneManager.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Kernel/HrCoreComponentEvent.h"
#include "Kernel/HrLog.h"
#include "Event/HrEvent.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrSceneNode::HrSceneNode() : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_strName = "NoName";
	m_bEnable = true;
	m_nodeType = NT_NORMAL;
	m_bRunning = false;
	m_pTransform = HrMakeSharedPtr<HrTransform>();
}

HrSceneNode::HrSceneNode(const std::string& strName) : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_strName = strName;
	m_bEnable = true;
	m_nodeType = NT_NORMAL;
	m_bRunning = false;
	m_pTransform = HrMakeSharedPtr<HrTransform>();
}

HrSceneNode::~HrSceneNode()
{
	m_vecChildrenNode.clear();
}

void HrSceneNode::SetName(const std::string& strName)
{
	m_strName = strName;
}

const std::string& HrSceneNode::GetName() const
{
	return m_strName;
}

void HrSceneNode::AddChild(const HrSceneNodePtr& pSceneNode)
{
	if (pSceneNode->GetParent() != nullptr)
	{
		HRERROR(_T("SceneNode AddChild Error! Already has parent"));
		return;
	}

	pSceneNode->SetParent(shared_from_this());
	if (IsRunning())
	{
		pSceneNode->OnEnter();
	}

	m_vecChildrenNode.push_back(pSceneNode);
}

void HrSceneNode::OnEnter()
{
	m_bRunning = true;

	AddEventListeners();

	if (m_pSceneObject)
	{
		m_pSceneObject->OnEnter();
	}
	for (auto& itemChild : m_vecChildrenNode)
	{
		itemChild->OnEnter();
	}
}

void HrSceneNode::OnExist()
{
	m_bRunning = false;
	for (auto& itemChild : m_vecChildrenNode)
	{
		itemChild->OnExist();
	}
}

void HrSceneNode::AddEventListeners()
{
	HrDirector::Instance()->GetEventComponent()->AddEventCustomListener(HrEvent::scEventBeginUpdateScene, std::bind(&HrSceneNode::OnBeginRenderScene, this, std::placeholders::_1), this);
	HrDirector::Instance()->GetEventComponent()->AddEventCustomListener(HrEvent::scEventEndUpdateScene, std::bind(&HrSceneNode::OnEndRenderScene, this, std::placeholders::_1), this);
}

void HrSceneNode::RemoveEventListeners()
{
	
}

void HrSceneNode::OnBeginRenderScene(const HrEventPtr& pEvent)
{
	
}

void HrSceneNode::OnEndRenderScene(const HrEventPtr& pEvent)
{

}

void HrSceneNode::FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue)
{
	if (this->m_bEnable)
	{
		if (m_pSceneObject && m_pSceneObject->GetRenderable() && m_pSceneObject->GetRenderable()->CanRender())
		{
			pRenderQueue->AddRenderable(m_pSceneObject->GetRenderable());
		}
		for (auto& item : m_vecChildrenNode)
		{
			item->FindVisibleRenderable(pRenderQueue);
		}
	}
}

void HrSceneNode::RemoveChildren()
{
	for (size_t i = 0; i < m_vecChildrenNode.size(); ++i)
	{
		m_vecChildrenNode[i]->OnExist();
	}
	m_vecChildrenNode.clear();
}

void HrSceneNode::UpdateNode(float fDt)
{
	m_pTransform->UpdateTransform(fDt);

	if (m_pSceneObject)
	{
		m_pSceneObject->Update(fDt, m_pTransform);
	}

	for (auto& iteChild : m_vecChildrenNode)
	{
		iteChild->UpdateNode(fDt);
	}

	m_pTransform->SetTransformDirty(false);
}

bool HrSceneNode::IsRunning() const
{
	return m_bRunning;
}

void HrSceneNode::SetParent(const HrSceneNodePtr& pParent)
{
	BOOST_ASSERT(pParent);
	if (pParent->IsRunning())
	{
		m_bRunning = true;
	}
	m_pParent = pParent;
	m_pTransform->SetParentTransform(pParent->GetTransform());
}

HrSceneNodePtr HrSceneNode::GetParent() const
{
	if (m_pParent.expired())
	{
		return nullptr;
	}
	else
	{
		return m_pParent.lock();
	}
}

const HrTransformPtr& HrSceneNode::GetTransform() const
{
	return m_pTransform;
}

HrSceneNode* HrSceneNode::GetChildByName(const std::string& strName) const
{
	for (auto& item : m_vecChildrenNode)
	{
		if (item->m_strName == strName)
		{
			return item.get();
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
		for (auto& itemChild : m_vecChildrenNode)
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

void HrSceneNode::SetSceneObject(const HrSceneObjectPtr& pSceneObj)
{
	m_pSceneObject = pSceneObj;
	m_pSceneObject->AttachSceneNode(shared_from_this());
}

const HrSceneObjectPtr& HrSceneNode::GetSceneObject()
{
	return m_pSceneObject;
}

