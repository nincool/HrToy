#ifndef _HR_RENDERQUEUE_H_
#define _HR_RENDERQUEUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderQueue 
	{
	public:
		~HrRenderQueue();

		void PrepareRenderQueue();
		void AddRenderable(const HrSceneNodePtr& pSceneNode);

		const std::vector<HrSceneNodePtr>& GetRenderables();
	protected:
		std::vector<HrSceneNodePtr> m_vecSceneNodes;
	};
}

#endif

