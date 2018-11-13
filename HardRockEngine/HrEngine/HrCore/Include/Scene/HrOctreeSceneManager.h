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

	protected:
		void RebuildOctree();

	protected:
		HrOctree* m_pOctree;

		std::vector<HrRenderablePtr> m_vecSceneRenderables;
	};
}


#endif
