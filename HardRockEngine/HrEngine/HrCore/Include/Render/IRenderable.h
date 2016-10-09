#ifndef _I_RENDERABLE_H_
#define _I_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class IRenderable 
	{
	public:
		virtual ~IRenderable(){}

		virtual IRenderLayout* GetRenderLayout() = 0;
		virtual IRenderTechnique* GetRenderTechnique() = 0;

		virtual void Update(HrRenderFrameParameters& renderFrameParameters) = 0;
	};
}

#endif



