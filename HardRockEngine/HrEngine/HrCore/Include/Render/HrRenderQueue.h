#ifndef _HR_RENDERQUEUE_H_
#define _HR_RENDERQUEUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	
	class HrRenderQueue 
	{
	public:
		~HrRenderQueue();

		enum EnumRenderQueueID
		{
			//RQ_QUEUE_BACKGROUND,
			RQ_QUEUE_MAIN,
			RQ_QUEUE_MAX
		};

		enum EnumOrganisationMode
		{
			OM_SORT_DESCENDING = 1,
			OM_SORT_ASCENDING,
		};

		void ClearRenderQueue();

		void AddRenderable(const HrRenderablePtr& pRenderable);

		const std::vector<HrRenderablePtr>& GetRenderables();

		void AddRenderableSceneNode(const HrSceneNodePtr& pSceneNode);

		/**
		 @Comment: 对渲染队列进行排序 [11/13/2018 By Hr]
		*/
		void Sort();

		void RenderRenderables();
	protected:
		EnumOrganisationMode m_organisationMode;
		std::vector<HrSceneNodePtr> m_vecRenderableNodes;

		std::vector<HrRenderablePtr> m_vecRenderables;
	};

	class HrRenderQueueManager
	{
	public:
		HrRenderQueueManager();
		~HrRenderQueueManager();

		void PrepareRenderQueue();
		void SortRenderQueue();

		void AddRenderableNode(const HrSceneNodePtr& pNode);

		const HrRenderQueuePtr& GetRenderQueue(HrRenderQueue::EnumRenderQueueID queueID);
	protected:
		std::array<HrRenderQueuePtr, HrRenderQueue::RQ_QUEUE_MAX> m_arrRenderQueue;
	};

}

#endif

