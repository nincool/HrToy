#include "Render/HrRenderQueue.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrRenderModule.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderProcessing.h"
#include "Render/HrRenderCommand.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObjectComponent.h"
#include "UI/HrUIWidget.h"


using namespace Hr;


//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////

void HrRenderCommandQueue::ClearRenderQueue()
{
	m_vecRenderCommands.clear();
}

void HrRenderCommandQueue::PushBack(HrRenderCommand* pCommand)
{
	m_vecRenderCommands.push_back(pCommand);
}

void HrRenderCommandQueue::Sort()
{
	if (m_vecRenderCommands.empty())
	{
		return;
	}
	//视矩阵z轴变换
	const HrCameraPtr& pCamera = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters()->GetActiveCamera();
	const float4& viewMatZ = pCamera->GetViewMatrix().Col(2);

	std::vector<std::pair<float, uint32>> vecMinDepths(m_vecRenderCommands.size());
	for (size_t i = 0; i < m_vecRenderCommands.size(); ++i)
	{
		HrRenderCommand* pRenderCommand = m_vecRenderCommands[i];
		//from klayge SceneManager.cpp 650
		const AABBox& aabb = pRenderCommand->GetTransform()->GetLocalAABBox();
		const Matrix4& mat = pRenderCommand->GetTransform()->GetWorldMatrix();
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
	std::vector<HrRenderCommand*> vecSortedCommands(vecMinDepths.size());
	for (size_t i = 0; i < vecMinDepths.size(); ++i)
	{
		vecSortedCommands[i] = m_vecRenderCommands[vecMinDepths[i].second];
	}
	m_vecRenderCommands.swap(vecSortedCommands);
}

void HrRenderCommandQueue::AcceptRenderProcessing(HrRenderProcessing* pProcessing)
{
	for (const auto& iteNode : m_vecRenderCommands)
	{
		pProcessing->VisitRenderCommand(iteNode);
	}
}

///////////////////////////////////////////////////////////////////
//HrRenderQueueManager
///////////////////////////////////////////////////////////////////
HrRenderQueueManager::HrRenderQueueManager()
{
	m_arrRenderCommandQueue[HrRenderCommandQueue::RQ_QUEUE_MAIN] = HrMakeSharedPtr<HrRenderCommandQueue>();
}

HrRenderQueueManager::~HrRenderQueueManager()
{

}

const HrRenderCommandQueuePtr& HrRenderQueueManager::GetRenderQueue(HrRenderCommandQueue::EnumRenderQueueID queueID)
{
	return m_arrRenderCommandQueue[queueID];
}

void HrRenderQueueManager::PrepareRenderQueue()
{
	for (auto& iteQueue : m_arrRenderCommandQueue)
	{
		if (iteQueue)
			iteQueue->ClearRenderQueue();
	}
}

void HrRenderQueueManager::SortRenderQueue()
{
	for (auto& iteQueue : m_arrRenderCommandQueue)
	{
		if (iteQueue)
			iteQueue->Sort();
	}
}


void HrRenderQueueManager::PushCommand(HrRenderCommand* pCommand)
{
	m_arrRenderCommandQueue[HrRenderCommandQueue::RQ_QUEUE_MAIN]->PushBack(pCommand);
}


