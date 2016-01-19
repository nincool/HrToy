#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrMain/Include/HrMainPrerequisiters.h"
#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_MAIN_API HrRenderable : public SceneObjAllocatedObject
	{
	public:
		HrRenderable();
		virtual ~HrRenderable();
	};
}

#endif



