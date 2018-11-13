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

		void InsertOctNode(const HrRenderablePtr& pRenderable);
	protected:
		HrOctNode* m_pRootNode;

		AABBox m_aabb;

		
	};
}

#endif
