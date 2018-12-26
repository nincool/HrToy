#ifndef _HR_OCTREESCENEMANAGER_H_
#define _HR_OCTREESCENEMANAGER_H_

#include "HrCore/Include/Scene/HrSceneManager.h"

namespace Hr
{
	class HrOctreeSceneManager : public HrSceneManager
	{
	public:
		HrOctreeSceneManager();
		~HrOctreeSceneManager();

		virtual void FindRenderablesToQueue() override;
	protected:
		void BuildOctTree();
		void RebuildOctree();
		void WalkOctree(const HrCameraPtr& pCamera);

	protected:
		HrOctree* m_pOctree;

		std::vector<HrSceneNodePtr> m_vecRenderableSceneNodes;
	};
}


#endif
