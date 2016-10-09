//Inspired by Ogre link :http://www.ogre3d.org/

#if HR_MEMORY_ALLOCATOR_STD != HR_MEMORY_ALLOCATOR_STD

#include "MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	/*

	Ugh, I wish I didn't have to do this.

	The problem is that operator new/delete are *implicitly* static. We have to
	instantiate them for each combination exactly once throughout all the compilation
	units that are linked together, and this appears to be the only way to do it.

	At least I can do it via templates.

	*/

	template class HrAllocatedObject<GeneralAllocPolicy>;
	template class HrAllocatedObject<GeometryAllocPolicy>;
	template class HrAllocatedObject<AnimationAllocPolicy>;
	template class HrAllocatedObject<SceneObjAllocPolicy>;
	template class HrAllocatedObject<ResourceAllocPolicy>;
	template class HrAllocatedObject<RenderSysAllocPolicy>;
}


#endif