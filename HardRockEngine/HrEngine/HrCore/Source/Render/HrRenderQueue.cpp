#include "Render/HrRenderQueue.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrLog.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFrameParameters.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObjectComponent.h"


using namespace Hr;

HrRenderQueue::~HrRenderQueue()
{

}

void HrRenderQueue::ClearRenderQueue()
{
	m_vecRenderableNodes.clear();

	m_vecRenderables.clear();
}

void HrRenderQueue::AddRenderableSceneNode(const HrSceneNodePtr& pSceneNode)
{
	m_vecRenderableNodes.push_back(pSceneNode);
}

void HrRenderQueue::Sort()
{
	HRLOG("RenderQueue::Sort RenderQueue's size [%d]", m_vecRenderableNodes.size());
	if (m_vecRenderableNodes.empty())
	{
		return;
	}
	//视矩阵z轴变换
	const HrCameraPtr& pCamera = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters()->GetActiveCamera();
	const float4& viewMatZ = pCamera->GetViewMatrix().Col(2);

	std::vector<std::pair<float, uint32>> vecMinDepths(m_vecRenderableNodes.size());
	for (size_t i = 0; i < m_vecRenderableNodes.size(); ++i)
	{
		const HrSceneNodePtr& pSceneNode = m_vecRenderableNodes[i];
		//from klayge SceneManager.cpp 650
		const AABBox& aabb = pSceneNode->GetTransform()->GetLocalAABBox();
		const Matrix4& mat = pSceneNode->GetTransform()->GetWorldMatrix();
		float md = std::numeric_limits<float>::infinity();
		//世界变换到视变换
		const float4 zvec(HrMath::Dot(mat.Row(0), viewMatZ),
			HrMath::Dot(mat.Row(1), viewMatZ),
			HrMath::Dot(mat.Row(2), viewMatZ),
			HrMath::Dot(mat.Row(3), viewMatZ));
		//AABB最近点
		for (int k = 0; k < 8; ++k)
		{
			const float3 v = aabb.Corner(k);
			md = std::min(md, v.x() * zvec.x() + v.y() * zvec.y() + v.z() * zvec.z() + zvec.w());
		}

		vecMinDepths[i] = std::make_pair(md, static_cast<uint32>(i));
	}
	
	std::sort(vecMinDepths.begin(), vecMinDepths.end());
	std::vector<HrSceneNodePtr> vecSortedNodes(vecMinDepths.size());
	for (size_t i = 0; i < vecMinDepths.size(); ++i)
	{
		vecSortedNodes[i] = m_vecRenderableNodes[vecMinDepths[i].second];
	}
	m_vecRenderableNodes.swap(vecSortedNodes);
}





void HrRenderQueue::AddRenderable(const HrRenderablePtr& pRenderable)
{
	m_vecRenderables.push_back(pRenderable);
}

const std::vector<HrRenderablePtr>& HrRenderQueue::GetRenderables()
{
	return m_vecRenderables;
}

void HrRenderQueue::RenderRenderables()
{
	for (const auto& iteNode : m_vecRenderableNodes)
	{
		HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters()->SetCurrentRenderable(iteNode->GetSceneObject()->GetRenderableComponent()->GetRenderable());
		iteNode->GetSceneObject()->GetRenderableComponent()->GetRenderable()->Render();
	}
}

///////////////////////////////////////////////////////////////////
//HrRenderQueueManager
///////////////////////////////////////////////////////////////////
HrRenderQueueManager::HrRenderQueueManager()
{
	//m_arrRenderQueue[HrRenderQueue::RQ_QUEUE_BACKGROUND] = HrMakeSharedPtr<HrRenderQueue>();
	m_arrRenderQueue[HrRenderQueue::RQ_QUEUE_MAIN] = HrMakeSharedPtr<HrRenderQueue>();
}

HrRenderQueueManager::~HrRenderQueueManager()
{

}

void HrRenderQueueManager::AddRenderableNode(const HrSceneNodePtr& pNode)
{
	//todo 
	auto pRenderQueue = GetRenderQueue(HrRenderQueue::RQ_QUEUE_MAIN);
	pRenderQueue->AddRenderableSceneNode(pNode);
}

const HrRenderQueuePtr& HrRenderQueueManager::GetRenderQueue(HrRenderQueue::EnumRenderQueueID queueID)
{
	return m_arrRenderQueue[queueID];
}

void HrRenderQueueManager::PrepareRenderQueue()
{
	for (auto& iteQueue : m_arrRenderQueue)
	{
		iteQueue->ClearRenderQueue();
	}
}

void HrRenderQueueManager::SortRenderQueue()
{
	for (auto& iteQueue : m_arrRenderQueue)
	{
		iteQueue->Sort();
	}
}

