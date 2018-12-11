#ifndef _HR_OCTNODE_H_
#define _HR_OCTNODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrOctNode
	{
	public:
		HrOctNode(const AABBox& aabb, int nDepth, bool bLeafNode = false);
		~HrOctNode();

		/**
			@Comment: 判断是否为叶子节点  [10/25/2018 By Hr]
			@Return: bool true or false
		*/
		bool IsLeafNode() const;
		
		/**
		 @Comment: 设置AABB [11/16/2018 By Hr]
		*/
		void SetAABB(const AABBox& aabb);
		const AABBox& GetAABB();

		/**
		 @Comment: 清除孩子节点 [11/16/2018 By Hr]
		*/
		void ClearChildren();

		void WalkTree(const HrCameraPtr& pCamera, const HrSceneNodePtr& pSceneNode, float fThreshold, int nMaxDepth);
	protected:
		void InitChildrenNode(int nMaxDepth);
		bool DetectNodeVisible(const HrCameraPtr& pCamera, float fThreshold);
		bool DetectDataVisible(const HrCameraPtr& pCamera, float fThreshold, const AABBox& dataAABB);
	protected:
		AABBox m_aabb;
		
		//当前深度
		int m_nDepth;
		
		//是否为叶子节点
		bool m_bLeafNode;

		//是否重新初始化了AABB
		bool m_bInitAABB;

		HrMath::EnumVisibility m_selfNV;
		
		std::array<HrOctNode*, 8> m_arrChildren;
	};
}

#endif
