#include "Scene/HrOctreeSceneManager.h"
#include "Scene/HrOctree.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRenderable.h"

using namespace Hr;


HrOctreeSceneManager::HrOctreeSceneManager()
{
	m_pOctree = new HrOctree();
}

HrOctreeSceneManager::~HrOctreeSceneManager()
{
	SAFE_DELETE(m_pOctree);
}

void HrOctreeSceneManager::RebuildOctree()
{
	//todo cached
	m_vecSceneRenderables.clear();
	GetRunningScene()->GetRootNode()->FindAllRenderables(m_vecSceneRenderables);

	AABBox aabbRoot(float3(0, 0, 0), float3(0, 0, 0));
	for (auto& renderable : m_vecSceneRenderables)
	{
		aabbRoot |= renderable->GetAABBox();
	}

	const float3& v3Center = aabbRoot.Center();
	//求出最大边长立方体
	const float3& v3Extent = aabbRoot.HalfSize();
	float fLongestDim = std::max(std::max(v3Extent.x(), v3Extent.y()), v3Extent.z());
	float3 v3NewExtent(fLongestDim, fLongestDim, fLongestDim);
	//用最大立方体初始化八叉树
	m_pOctree->InitOctree(AABBox(v3Center - v3NewExtent, v3Center + v3NewExtent));

	//构建八叉树
	for (auto& renderable : m_vecSceneRenderables)
	{
		m_pOctree->InsertOctNode(renderable);
	}
}


