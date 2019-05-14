#ifndef _HR_RENDERQUEUE_H_
#define _HR_RENDERQUEUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	//////////////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////////////

	class HrRenderCommandQueue
	{
	public:
		enum EnumRenderQueueID
		{
		
			/// The default render queue
			RQ_QUEUE_MAIN = 0,

			QUEUE_COUNT,
		};

		void ClearRenderQueue();
		void PushBack(HrRenderCommand* pCommand);
		/**
			@Comment: 对渲染队列进行排序 [11/13/2018 By Hr]
		*/
		void Sort();

		virtual void AcceptRenderProcessing(HrRenderProcessing* pProcessing);
	public:
		std::vector<HrRenderCommand*> m_vecRenderCommands;
	};

	//////////////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////////////
	class HrRenderQueueManager
	{
	public:
		HrRenderQueueManager();
		~HrRenderQueueManager();

		void PrepareRenderQueue();
		void SortRenderQueue();

		void PushCommand(HrRenderCommand* pCommand);
		const HrRenderCommandQueuePtr& GetRenderQueue(HrRenderCommandQueue::EnumRenderQueueID queueID = HrRenderCommandQueue::RQ_QUEUE_MAIN);
	protected:
		std::array<HrRenderCommandQueuePtr, HrRenderCommandQueue::QUEUE_COUNT> m_arrRenderCommandQueue;
	};

}

#endif

