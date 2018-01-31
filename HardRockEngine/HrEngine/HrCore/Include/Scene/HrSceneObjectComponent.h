#ifndef _HR_SCENEOBJECTCOMPONENT_H_
#define _HR_SCENEOBJECTCOMPONENT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/Include/HrComponent.h"

namespace Hr
{
	class HR_CORE_API HrSceneObjectComponent : public HrComponent
	{
	public:
		HrSceneObjectComponent(const std::string& strName);
		~HrSceneObjectComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;

		const std::string& GetName();
	protected:
		std::string m_strName;
	};
}

#endif


