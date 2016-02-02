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


		virtual void RunScene(const IScenePtr& pScene);


	private:
		IScenePtr m_pShareRunningScene;
	};
}

#endif




