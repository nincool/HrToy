#ifndef _HR_SCENEOBJECT_H_
#define _HR_SCENEOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrSceneObject
	{
	public:
		HrSceneObject();
		HrSceneObject(const std::string& strName);
		HrSceneObject(const std::string& strName, const HrRenderablePtr& pRenderable);
		~HrSceneObject();

		void SetName(const std::string& strName);
		const std::string& GetName();

		void AttachRenderable(const HrRenderablePtr& pRenderable);
		const HrRenderablePtr& GetRenderable();
	protected:
		std::string m_strName;

		HrRenderablePtr m_pRenderable;
		
	};
}

#endif


