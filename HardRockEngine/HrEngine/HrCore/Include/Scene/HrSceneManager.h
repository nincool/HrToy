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

		virtual void FindRenderablesToQueue(const HrCameraPtr& pCamera);
		virtual void FindEffectLights();

		void RenderVisibleObjects(HrRenderProcessing* pProcessing);

		void SetSceneDirty();
	protected:
		bool CheckSceneRunning();
	protected:
		//�Ƿ���Scene����
		bool m_bSceneRunning;
		
		//�����е�Scene
		HrScenePtr m_pRunningScene;
		
		//�Ƿ���Ҫ�ؽ�Scene�ṹ oct
		bool m_bDirtyScene;


		HrRenderFrameParametersPtr m_pRenderParameters;

		HrRenderQueuePtr m_pRenderQueue;

		//��Ⱦ����
		HrRenderQueueManagerPtr m_pRenderQueueManager;

		


	};
}

#endif




