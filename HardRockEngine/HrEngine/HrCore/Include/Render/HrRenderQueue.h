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
		void AddRenderable(const HrRenderablePtr& pRenderable);

		const std::vector<HrRenderablePtr>& GetRenderables();
	protected:
		std::vector<HrRenderablePtr> m_vecRenderables;
	};
}

#endif

