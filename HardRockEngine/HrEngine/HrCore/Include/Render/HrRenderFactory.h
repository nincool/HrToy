#ifndef _HR_RENDERFACTORY_H_
#define _HR_RENDERFACTORY_H_

#include "HrCore/Include/Render/IRenderFactory.h"

namespace Hr
{
	class HR_CORE_API HrRenderFactory : public IRenderFactory
	{
	public:
		HrRenderFactory();
		~HrRenderFactory();

	public:
		virtual void CreateRender() override;
	};
}


#endif


