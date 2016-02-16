#ifndef _HR_RENDERQUEUE_H_
#define _HR_RENDERQUEUE_H_

#include "HrCore/Include/Render/IRenderQueue.h"

namespace Hr
{
	class HrRenderQueue : public IRenderQueue
	{
	public:
		~HrRenderQueue();

		virtual void PrepareRenderQueue() override;
		virtual void AddRenderable(ISceneNode* pSceneNode) override;

	protected:
		std::unordered_map<IRenderable*, ISceneNode*> m_mapRenderQueue;
	};
}

#endif

