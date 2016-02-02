#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/Scene/IScene.h"

namespace Hr
{
	class HrScene : public IScene
	{
	public:
		HrScene();
		~HrScene();

		virtual void OnEnter() override;
		virtual void OnEnterDidFinish() override;

	private:
		HrSceneManagerPtr m_pShareSceneManager;
	};
}

#endif

