#ifndef _HR_OCTNODE_H_
#define _HR_OCTNODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrOctNode
	{
	public:
		HrOctNode(const AABBox& aabb, int nDepth);
		~HrOctNode();

		/**
			@Comment: 判断是否为叶子节点  [10/25/2018 By Hr]
			@Return: bool true or false
		*/
		bool IsLeafNode() const;

		void InsertChild(const HrRenderablePtr& pRenderable, int nMaxDepth);
	protected:
		void CreateChildren();
	protected:
		std::vector<HrOctNode*> m_vecChildren;
		std::vector<HrRenderablePtr> m_vecDatas;
		AABBox m_aabb;

		int m_nDepth;
	};
}

#endif
