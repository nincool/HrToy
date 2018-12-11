#ifndef _HR_OCTREE_H_
#define _HR_OCTREE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrOctree
	{
	public:
		HrOctree();
		~HrOctree();

		void InitOctree(const AABBox& aabb);
		const AABBox& GetAABB();

		void Clear();

		void WalkTree(const HrCameraPtr& pCamera, const HrSceneNodePtr& pSceneNode);
	protected:
		HrOctNode* m_pRootNode;
		AABBox m_aabb;
		float m_fThreshold;
		static const int m_sc_nMaxDepth = 3;

		
	};
}

#endif
