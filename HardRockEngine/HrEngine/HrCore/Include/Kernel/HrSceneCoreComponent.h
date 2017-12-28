#ifndef _HR_SCENECORECOMPONENT_H_
#define _HR_SCENECORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"

namespace Hr
{
	class HrSceneCoreComponent : public HrCoreComponent
	{
	public:
		enum class EnumSceneManagerType
		{
			SMT_NORMAL,
		};
	public:
		HrSceneCoreComponent(EnumSceneManagerType sceneManagerType = EnumSceneManagerType::SMT_NORMAL);
		~HrSceneCoreComponent();

		bool Update(float fDelta) override;

		void RunScene(const HrScenePtr& pScene);
		void StopScene();

		void RenderScene();
		void Destroy();

		const HrScenePtr& GetRunningScene() const;
	private:
		bool CreateSceneManager(EnumSceneManagerType sceneManagerType);
	private:
		HrSceneManagerPtr m_pSceneManager;
	};
}

#endif
