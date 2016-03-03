#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/Scene/IScene.h"

namespace Hr
{
	class HR_CORE_API HrScene : public IScene
	{
	public:
		HrScene();
		~HrScene();

		virtual void OnEnter() override;
		virtual void OnEnterDidFinish() override;
		virtual void OnExit() override;

		virtual void AddSceneNode(ISceneNode* pSceneNode) override;
		virtual void ClearSceneNode() override;

		virtual void Update() override;
		virtual void FillRenderQueue(IRenderQueuePtr& pRenderQueue) override;

	private:
		ISceneManagerPtr m_pShareSceneManager;
		ISceneNodePtr m_pShareRootNode;
	};
}

#endif

