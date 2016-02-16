#ifndef _HR_SCENEMANAGER_H_
#define _HR_SCENEMANAGER_H_

#include "ISceneManager.h"

namespace Hr
{
	class HrSceneManager : public ISceneManager
	{
	public:
		HrSceneManager();
		~HrSceneManager();

		virtual void RunScene(const IScenePtr& pScene) override;

		virtual void UpdateScene() override;
	private:
		IScenePtr m_pShareRunningScene;
		IRenderQueuePtr m_pShareRenderQueue;
	};
}

#endif




