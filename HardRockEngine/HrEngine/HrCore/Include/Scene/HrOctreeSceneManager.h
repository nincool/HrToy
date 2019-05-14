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

		virtual void FindRenderablesToQueue(const HrCameraPtr& pCamera) override;
	protected:
		void BuildOctTree(const HrCameraPtr& pCamera);
		void RebuildOctree(const HrCameraPtr& pCamera);
		void WalkOctree(const HrCameraPtr& pCamera);

	protected:
		HrOctree* m_pOctree;

		std::vector<HrSceneNode*> m_vecRenderableSceneNodes;
	};
}


#endif
