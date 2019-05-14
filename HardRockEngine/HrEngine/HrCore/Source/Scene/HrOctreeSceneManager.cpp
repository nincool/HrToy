#include "Scene/HrOctreeSceneManager.h"
#include "Scene/HrOctree.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObject.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrSkyBox.h"

using namespace Hr;


HrOctreeSceneManager::HrOctreeSceneManager()
{
	m_pOctree = new HrOctree();
	
}

HrOctreeSceneManager::~HrOctreeSceneManager()
{
	SAFE_DELETE(m_pOctree);
}

void HrOctreeSceneManager::FindRenderablesToQueue(const HrCameraPtr& pCamera)
{
	m_pRenderQueueManager->PrepareRenderQueue();

	uint32 nCameraMaskLayer = pCamera->GetCameraMaskLayer();

	WalkOctree(pCamera);
	
	for (size_t i = 0; i < m_vecRenderableSceneNodes.size(); ++i)
	{
		if (m_vecRenderableSceneNodes[i]->GetFrustumVisible() == HrMath::NV_FULL)
		{
			m_pRenderQueueManager->PushCommand(m_vecRenderableSceneNodes[i]->GetSceneObject()->GetRenderCommand());
		}
	}

	//add sky box
	if (m_pRunningScene->GetEnvironmentData()->IsSkyBoxEnable())
	{
		m_pRenderQueueManager->PushCommand(m_pRunningScene->GetEnvironmentData()->GetSkyBox()->GetAttachSceneObject()->GetRenderCommand());
	}

	//sort
	m_pRenderQueueManager->SortRenderQueue();
}

void HrOctreeSceneManager::WalkOctree(const HrCameraPtr& pCamera)
{
	BuildOctTree(pCamera);

	//判断该节点是否在摄像机范围内
	const AABBox& octTreeAABB = m_pOctree->GetAABB();
	HrMath::EnumVisibility bo = HrMath::Map(pCamera->ViewFrustum().Intersect(octTreeAABB));
	if (bo == HrMath::NV_NONE)
	{
		return;
	}
	else
	{
		for (size_t i = 0; i < m_vecRenderableSceneNodes.size(); ++i)
		{
			m_pOctree->WalkTree(pCamera, m_vecRenderableSceneNodes[i]);
		}
	}
}

void HrOctreeSceneManager::BuildOctTree(const HrCameraPtr& pCamera)
{
	if (m_bDirtyScene)
	{
		RebuildOctree(pCamera);
		m_bDirtyScene = false;
	}
}

void HrOctreeSceneManager::RebuildOctree(const HrCameraPtr& pCamera)
{
	m_pOctree->Clear();
	m_vecRenderableSceneNodes.clear();
	GetRunningScene()->GetRootNode()->FindAllRenderables(m_vecRenderableSceneNodes, pCamera->GetCameraMaskLayer());
	if (m_vecRenderableSceneNodes.empty())
	{
		return;
	}

	AABBox aabbRoot(float3(0, 0, 0), float3(0, 0, 0));
	for (auto& renderable : m_vecRenderableSceneNodes)
	{
		renderable->SetFrustumVisible(HrMath::NV_UNKNOWN);
		aabbRoot |= renderable->GetTransform()->GetWorldAABBox();
	}

	const float3& v3Center = aabbRoot.Center();
	//求出最大边长立方体
	const float3& v3Extent = aabbRoot.HalfSize();
	float fLongestDim = std::max(std::max(v3Extent.x(), v3Extent.y()), v3Extent.z());
	float3 v3NewExtent(fLongestDim, fLongestDim, fLongestDim);
	//用最大立方体初始化八叉树
	m_pOctree->InitOctree(AABBox(v3Center - v3NewExtent, v3Center + v3NewExtent));
}
