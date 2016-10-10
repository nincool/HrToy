#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrScene 
	{
	public:
		HrScene();
		virtual ~HrScene();

		virtual void OnEnter();
		virtual void OnEnterDidFinish();
		virtual void OnExit();

		virtual void AddSceneNode(HrSceneNode* pSceneNode);
		virtual void ClearSceneNode();

		virtual void Update();
		virtual void FillRenderQueue(HrRenderQueuePtr& pRenderQueue);

	private:
		HrSceneNodePtr m_pRootNode;
	};
}

#endif

