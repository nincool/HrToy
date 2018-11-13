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

		virtual void UpdateScene(float fDeltaTime);
		virtual void RenderScene();
		virtual void Destroy();
	
		const HrScenePtr& GetRunningScene();
		const HrRenderFrameParametersPtr& GetRenderFrameParamPtr();
	protected:
		bool CheckSceneRunning();
	
	protected:
		HrScenePtr m_pRunningScene;
		HrRenderQueuePtr m_pRenderQueue;

		bool m_bSceneRunning;

		HrRenderFrameParametersPtr m_pRenderParameters;

	};
}

#endif




