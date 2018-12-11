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

		void RenderVisibleObjects();

		//todo new 
		virtual void FindVisibleSceneNodes(const HrCameraPtr& pCamera, const HrRenderQueueManagerPtr& pRenderQueue);

		void SetSceneDirty();
	protected:
		bool CheckSceneRunning();
	
	protected:
		//是否有Scene启动
		bool m_bSceneRunning;
		
		//当运行的Scene
		HrScenePtr m_pRunningScene;
		
		//是否需要重建Scene结构 oct
		bool m_bDirtyScene;


		HrRenderFrameParametersPtr m_pRenderParameters;





		HrRenderQueuePtr m_pRenderQueue;

		//渲染队列
		HrRenderQueueManagerPtr m_pRenderQueueManager;

		


	};
}

#endif




