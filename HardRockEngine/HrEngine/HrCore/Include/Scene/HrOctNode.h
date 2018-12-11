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
			@Comment: �ж��Ƿ�ΪҶ�ӽڵ�  [10/25/2018 By Hr]
			@Return: bool true or false
		*/
		bool IsLeafNode() const;
		
		/**
		 @Comment: ����AABB [11/16/2018 By Hr]
		*/
		void SetAABB(const AABBox& aabb);
		const AABBox& GetAABB();

		/**
		 @Comment: ������ӽڵ� [11/16/2018 By Hr]
		*/
		void ClearChildren();

		void WalkTree(const HrCameraPtr& pCamera, const HrSceneNodePtr& pSceneNode, float fThreshold, int nMaxDepth);
	protected:
		void InitChildrenNode(int nMaxDepth);
		bool DetectNodeVisible(const HrCameraPtr& pCamera, float fThreshold);
		bool DetectDataVisible(const HrCameraPtr& pCamera, float fThreshold, const AABBox& dataAABB);
	protected:
		AABBox m_aabb;
		
		//��ǰ���
		int m_nDepth;
		
		//�Ƿ�ΪҶ�ӽڵ�
		bool m_bLeafNode;

		//�Ƿ����³�ʼ����AABB
		bool m_bInitAABB;

		HrMath::EnumVisibility m_selfNV;
		
		std::array<HrOctNode*, 8> m_arrChildren;
	};
}

#endif
