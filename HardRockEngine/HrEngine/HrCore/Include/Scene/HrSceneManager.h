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
		virtual void StopScene() override;

		virtual void UpdateScene() override;
		virtual void Destroy() override;
	protected:
		void FlushScene();
		bool CheckSceneRunning();
	private:
		IScenePtr m_pShareRunningScene;
		IRenderQueuePtr m_pShareRenderQueue;

		bool m_bSceneRunning;
	};
}

#endif




