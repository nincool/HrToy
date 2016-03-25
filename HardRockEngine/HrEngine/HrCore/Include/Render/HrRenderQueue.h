#ifndef _HR_RENDERQUEUE_H_
#define _HR_RENDERQUEUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrRenderQueue : public RenderSysAllocatedObject
	{
	public:
		~HrRenderQueue();

		void PrepareRenderQueue();
		void AddRenderable(HrSceneNode* pSceneNode);

		std::unordered_map<IRenderable*, HrSceneNode*>& GetRenderables();
	protected:
		std::unordered_map<IRenderable*, HrSceneNode*> m_mapRenderQueue;
	};
}

#endif

