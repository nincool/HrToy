#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrInstanceBatchHW.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneManager.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrEventSystemModule.h"
#include "Kernel/HrLog.h"
#include "Event/HrEvent.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrSceneNode::HrSceneNode() : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_strName = "NoName";
	m_bEnable = true;
	m_bRunning = false;
	m_pParentNode = nullptr;
	m_pTransform = HrMakeSharedPtr<HrTransform>(this);
	m_pSceneObject = HrMakeSharedPtr<HrSceneObject>(this);
}

HrSceneNode::HrSceneNode(const std::string& strName) : HrIDObject(HrID::GenerateID<HrSceneNode>())
{
	m_strName = strName;
	m_bEnable = true;
	m_bRunning = false;
	m_pParentNode = nullptr;
	m_pTransform = HrMakeSharedPtr<HrTransform>(this);
	m_pSceneObject = HrMakeSharedPtr<HrSceneObject>(this);
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

	pSceneNode->SetParent(this);
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
	m_pParentNode = nullptr;
	for (auto& itemChild : m_vecChildrenNode)
	{
		itemChild->OnExist();
	}
}

void HrSceneNode::AddEventListeners()
{
	HrDirector::Instance()->GetEventSystemModule()->AddEventCustomListener(HrEvent::scEventBeginUpdateScene, std::bind(&HrSceneNode::OnBeginRenderScene, this, std::placeholders::_1), this);
	HrDirector::Instance()->GetEventSystemModule()->AddEventCustomListener(HrEvent::scEventEndUpdateScene, std::bind(&HrSceneNode::OnEndRenderScene, this, std::placeholders::_1), this);
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
		if (m_pSceneObject)
		{
			const HrRenderableComponentPtr& pRenderableCom = m_pSceneObject->GetRenderableComponent();
			if (pRenderableCom)
			{
				const HrInstanceBatchComponentPtr pBatchCom = m_pSceneObject->GetComponent<HrInstanceBatchComponent>();
				if (pBatchCom)
				{
					HrRenderablePtr pRenderable = pBatchCom->GetInstanceBatch();
					pRenderQueue->AddRenderable(pRenderable);
				}
				else
				{
					pRenderQueue->AddRenderable(pRenderableCom->GetRenderable());
				}
			}
		}
		for (auto& item : m_vecChildrenNode)
		{
			item->FindVisibleRenderable(pRenderQueue);
		}
	}
}

void HrSceneNode::FindAllRenderables(std::vector<HrRenderablePtr>& vecRenderables)
{
	if (m_bEnable)
	{
		BOOST_ASSERT(m_pSceneObject);
		const HrRenderableComponentPtr& pRenderableCom = m_pSceneObject->GetRenderableComponent();
		if (pRenderableCom)
		{
			//todo batch
			vecRenderables.push_back(pRenderableCom->GetRenderable());
		}
		for (auto& item : m_vecChildrenNode)
		{
			item->FindAllRenderables(vecRenderables);
		}
	}
}

bool HrSceneNode::RemoveChild(const HrSceneNodePtr& pChild)
{
	for (size_t i = 0; i < m_vecChildrenNode.size(); ++i)
	{
		if (m_vecChildrenNode[i] == pChild)
		{
			pChild->OnExist();
			m_vecChildrenNode.erase(m_vecChildrenNode.begin() + i);
			
			return true;
		}
	}

	return false;
}

void HrSceneNode::RemoveChildren()
{
	for (size_t i = 0; i < m_vecChildrenNode.size(); ++i)
	{
		m_vecChildrenNode[i]->OnExist();
	}
	m_vecChildrenNode.clear();
}

bool HrSceneNode::RemoveFromParent()
{
	if (m_pParentNode)
	{
		return m_pParentNode->RemoveChild(shared_from_this());
	}

	return false;
}

void HrSceneNode::UpdateNode(float fDt)
{
	m_pTransform->UpdateTransform(fDt);

	if (m_pSceneObject)
	{
		m_pSceneObject->Update(fDt);
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

void HrSceneNode::SetParent(HrSceneNode* pParentNode)
{
	m_pParentNode = pParentNode;
	if (m_pParentNode->IsRunning())
	{
		m_bRunning = true;
	}
}

const HrSceneNode* HrSceneNode::GetParent() const
{
	return m_pParentNode;
}

const HrTransformPtr& HrSceneNode::GetTransform() const
{
	return m_pTransform;
}

const HrSceneNodePtr& HrSceneNode::GetChildByName(const std::string& strName) const
{
	for (auto& item : m_vecChildrenNode)
	{
		if (item->m_strName == strName)
		{
			return item;
		}
	}
	return nullptr;
}

const HrSceneNodePtr& HrSceneNode::GetNodeByNameFromHierarchy(const std::string& strName)
{
	if (this->m_strName == strName)
	{
		return shared_from_this();
	}
	else
	{
		for (auto& itemChild : m_vecChildrenNode)
		{
			const HrSceneNodePtr& pResult = itemChild->GetNodeByNameFromHierarchy(strName);
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

const HrSceneObjectPtr& HrSceneNode::GetSceneObject()
{
	return m_pSceneObject;
}

void HrSceneNode::DirtyTransfrom(bool bDirtyPos, bool bDirtyScale, bool bDirtyOrientation)
{
	if (m_pSceneObject)
		m_pSceneObject->OnNodeTransformDirty(m_pTransform);
	for (auto& iteChild : m_vecChildrenNode)
	{
		iteChild->GetTransform()->DirtyTransform(bDirtyPos, bDirtyScale, bDirtyOrientation);
	}
}

const HrSceneNodePtr& HrSceneNode::GetChildByIndex(int nNodeIndex)
{
	if (0 <= nNodeIndex && nNodeIndex < m_vecChildrenNode.size())
	{
		return m_vecChildrenNode[nNodeIndex];
	}

	return nullptr;
}

size_t HrSceneNode::GetChildrenCount()
{
	return m_vecChildrenNode.size();
}


