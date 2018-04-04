#ifndef _HR_SCENECORECOMPONENT_H_
#define _HR_SCENECORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"

namespace Hr
{
	class HR_CORE_API HrCoreComponentScene : public HrCoreComponent
	{
	public:
		enum class EnumSceneManagerType
		{
			SMT_NORMAL,
		};
	public:
		HrCoreComponentScene(EnumSceneManagerType sceneManagerType = EnumSceneManagerType::SMT_NORMAL);
		~HrCoreComponentScene();

		bool Update(float fDelta) override;

		void RunScene(const HrScenePtr& pScene);
		void StopScene();

		void RenderScene();
		void Destroy();

		const HrScenePtr& GetRunningScene() const;

		const HrRenderFrameParametersPtr& GetRenderFrameParameters();
	private:
		bool CreateSceneManager(EnumSceneManagerType sceneManagerType);
	private:
		HrSceneManagerPtr m_pSceneManager;

		HrEventPtr m_pEventUpdateBegin;
		HrEventPtr m_pEventUpdateEnd;
	};
}

#endif
