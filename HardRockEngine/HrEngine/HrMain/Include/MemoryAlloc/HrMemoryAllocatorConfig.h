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

	/// Allocate a block of raw memory, and indicate the category of usage
#   define OGRE_MALLOC(bytes, category) ::Ogre::CategorisedAllocPolicy<category>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
	/// Allocate a block of memory for a primitive type, and indicate the category of usage
#   define OGRE_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
	/// Free the memory allocated with OGRE_MALLOC or OGRE_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)

	/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#   define OGRE_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
	/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
	/// Free the memory allocated with OGRE_NEW_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}

	// aligned allocation
	/// Allocate a block of raw memory aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_MALLOC_SIMD(bytes, category) ::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
	/// Allocate a block of raw memory aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_MALLOC_ALIGN(bytes, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
	/// Allocate a block of memory for a primitive type aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_SIMD(T, count, category) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
	/// Allocate a block of memory for a primitive type aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_ALIGN(T, count, category, align) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
	/// Free the memory allocated with either OGRE_MALLOC_SIMD or OGRE_ALLOC_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_SIMD(ptr, category) ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr)
	/// Free the memory allocated with either OGRE_MALLOC_ALIGN or OGRE_ALLOC_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_ALIGN(ptr, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr)

	/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#   define OGRE_NEW_T_SIMD(T, category) new (::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
	/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_SIMD(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
	/// Free the memory allocated with OGRE_NEW_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_SIMD(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T_SIMD. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_SIMD(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr);}
	/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#   define OGRE_NEW_T_ALIGN(T, category, align) new (::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
	/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_ALIGN(T, count, category, align) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
	/// Free the memory allocated with OGRE_NEW_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_ALIGN(ptr, T, category, align) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T_ALIGN. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_ALIGN(ptr, T, count, category, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr);}

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

	/// Allocate a block of raw memory, and indicate the category of usage
#   define OGRE_MALLOC(bytes, category) ::Ogre::CategorisedAllocPolicy<category>::allocateBytes(bytes)
	/// Allocate a block of memory for a primitive type, and indicate the category of usage
#   define OGRE_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count)))
	/// Free the memory allocated with OGRE_MALLOC or OGRE_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)

	/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#   define OGRE_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T))) T
	/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count))), count) 
	/// Free the memory allocated with OGRE_NEW_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}

	// aligned allocation
	/// Allocate a block of raw memory aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_MALLOC_SIMD(bytes, category) ::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(bytes)
	/// Allocate a block of raw memory aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_MALLOC_ALIGN(bytes, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(bytes)
	/// Allocate a block of memory for a primitive type aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_SIMD(T, count, category) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count)))
	/// Allocate a block of memory for a primitive type aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_ALIGN(T, count, category, align) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count)))
	/// Free the memory allocated with either OGRE_MALLOC_SIMD or OGRE_ALLOC_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_SIMD(ptr, category) ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr)
	/// Free the memory allocated with either OGRE_MALLOC_ALIGN or OGRE_ALLOC_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_ALIGN(ptr, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr)

	/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#   define OGRE_NEW_T_SIMD(T, category) new (::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T))) T
	/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_SIMD(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count))), count) 
	/// Free the memory allocated with OGRE_NEW_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_SIMD(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T_SIMD. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_SIMD(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr);}
	/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#   define OGRE_NEW_T_ALIGN(T, category, align) new (::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T))) T
	/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_ALIGN(T, count, category, align) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count))), count) 
	/// Free the memory allocated with OGRE_NEW_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_ALIGN(ptr, T, category, align) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr);}
	/// Free the memory allocated with OGRE_NEW_ARRAY_T_ALIGN. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_ALIGN(ptr, T, count, category, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr);}

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

