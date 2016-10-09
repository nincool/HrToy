#ifndef _HR_SCENEMANAGER_H_
#define _HR_SCENEMANAGER_H_

#include "HrCorePrerequisite.h"

namespace Hr
{
	class HrSceneManager 
	{
	public:
		HrSceneManager();
		~HrSceneManager();

		virtual void RunScene(const HrScenePtr& pScene);
		virtual void StopScene();

		virtual void UpdateScene();
		virtual void RenderScene(IRenderTargetPtr& renderTarget);
		virtual void Destroy();
	
	protected:
		void FlushScene();
		bool CheckSceneRunning();
	
	private:
		HrScenePtr m_pShareRunningScene;
		HrRenderQueuePtr m_pShareRenderQueue;
		HrCamera* m_pCurrentCamera;

		bool m_bSceneRunning;

		HrRenderFrameParametersPtr m_pUniqueRenderParameters;
	};
}

#endif




