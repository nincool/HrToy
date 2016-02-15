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

		virtual const ISceneNodePtr& GetRootNode() override;
		virtual void RunScene(const IScenePtr& pScene) override;

	private:
		ISceneNodePtr m_pShareRootNode;
		IScenePtr m_pShareRunningScene;
	};
}

#endif




