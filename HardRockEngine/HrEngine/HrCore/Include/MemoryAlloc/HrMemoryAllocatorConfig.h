#ifndef _HR_MEMORYALLOCATORCONFIG_H_
#define _HR_MEMORYALLOCATORCONFIG_H_

#include "HrMemoryNedAlloc.h"
#include "HrMemoryNedPooling.h"
#include "HrMemoryAllocatedObject.h"

namespace Hr
{
	/** A set of categories that indicate the purpose of a chunk of memory
	being allocated.
	These categories will be provided at allocation time in order to allow
	the allocation policy to vary its behaviour if it wishes. This allows you
	to use a single policy but still have variant behaviour. The level of
	control it gives you is at a higher level than assigning different
	policies to different classes, but is the only control you have over
	general allocations that are primitive types.
	*/
	enum MemoryCategory
	{
		/// General purpose
		MEMCATEGORY_GENERAL = 0,
		/// Geometry held in main memory
		MEMCATEGORY_GEOMETRY,
		/// Animation data like tracks, bone matrices
		MEMCATEGORY_ANIMATION,
		/// Scene object instances
		MEMCATEGORY_SCENE_OBJECTS,
		/// Other resources
		MEMCATEGORY_RESOURCE,
		/// Rendersystem structures
		MEMCATEGORY_RENDERSYS,
	};

	// configure default allocators based on the options above
	// notice how we're not using the memory categories here but still roughing them out
	// in your allocators you might choose to create different policies per category

	// configurable category, for general malloc
	// notice how we ignore the category here, you could specialise

#if HR_MEMORY_ALLOCATOR == HR_MEMORY_ALLOCATOR_NEDPOOLING
	template <MemoryCategory Cat> class HrCategorisedAllocPolicy : public HrNedPoolingPolicy{};
	template <MemoryCategory Cat, size_t align = 0> class HrCategorisedAlignAllocPolicy : public HrNedPoolingAlignedPolicy< align > {};
#elif HR_MEMORY_ALLOCATOR == HR_MEMORY_ALLOCATOR_NED
	template <MemoryCategory cat> class HrCategorisedAllocPolicy : public HrNedAllocPolicy{};
	template <MemoryCategory Cat, size_t align = 0> class HrCategorisedAlignAllocPolicy : public HrNedAlignedAllocPolicy < align > {};
#endif

	// Useful shortcuts
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_GENERAL> GeneralAllocPolicy;
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_GEOMETRY> GeometryAllocPolicy;
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_ANIMATION> AnimationAllocPolicy;
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_SCENE_OBJECTS> SceneObjAllocPolicy;
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_RESOURCE> ResourceAllocPolicy;
	typedef HrCategorisedAllocPolicy<Hr::MEMCATEGORY_RENDERSYS> RenderSysAllocPolicy;

	//注意多继承会导致回收错误 (delete parent)
	typedef HrAllocatedObject<GeneralAllocPolicy> GeneralAllocatedObject;
	typedef HrAllocatedObject<GeometryAllocPolicy> GeometryAllocatedObject;
	typedef HrAllocatedObject<AnimationAllocPolicy> AnimationAllocatedObject;
	typedef HrAllocatedObject<SceneObjAllocPolicy> SceneObjAllocatedObject;
	typedef HrAllocatedObject<ResourceAllocPolicy> ResourceAllocatedObject;
	typedef HrAllocatedObject<RenderSysAllocPolicy> RenderSysAllocatedObject;
	

#if (HR_DEBUG > 0)

	// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
	// Also hooks up the file/line/function params
	// Can only be used with classes that derive from AllocatedObject since customised new/delete needed
#   define HR_NEW new (__FILE__, __LINE__, __FUNCTION__)
#   define HR_DELETE delete

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif // SAFE_DELETE
#	define SAFE_DELETE(p) HR_DELETE p; p = nullptr
#else // !OGRE_DEBUG_MODE

	// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
#   define HR_NEW new 
#   define HR_DELETE delete

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif // SAFE_DELETE
#	define SAFE_DELETE(p) (HR_DELETE p; p = nullptr);
#endif // OGRE_DEBUG_MODE
}

#endif

