/************************************************************************
*
* @Comment：参考学习Ogre
*
* @Author: Hr
* @Date: [12/3/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_MEMORYNEDPOOLING_H_
#define _HR_MEMORYNEDPOOLING_H_

#include "../HrMainPrerequisiters.h"
#include <limits>

namespace Hr
{
#if HR_MEMORY_ALLOCATOR == HR_MEMORY_ALLOCATOR_NEDPOOLING
	
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Memory
	*  @{
	*/
	/** Non-templated utility class just to hide nedmalloc.
	*/
	class HrNedPoolingImpl
	{
	public:
		static void* AllocBytes(size_t count, const char* file, int line, const char* func);
		static void DeallocBytes(void* ptr);

		static void* AllocBytesAligned(size_t align, size_t count, const char* file, int line, const char* func);
		static void DeallocBytesAligned(size_t align, void* ptr);
	};

	/** An allocation policy for use with AllocatedObject and
	STLAllocator. This is the class that actually does the allocation
	and deallocation of physical memory, and is what you will want to
	provide a custom version of if you wish to change how memory is allocated.
	@par
	This allocation policy uses nedmalloc
	(http://nedprod.com/programs/portable/nedmalloc/index.html).
	*/
	class HR_MAIN_API HrNedPoolingPolicy
	{
	public:
		static inline void* AllocateBytes(size_t cout, const char* file = 0, int line = 0, const char* func = 0)
		{
			return HrNedPoolingImpl::AllocBytes(cout, file, line, func);
		}

		static inline void DeallocateBytes(void* ptr)
		{
			HrNedPoolingImpl::DeallocBytes(ptr);
		}

		/// Get the maximum size of a single allocation
		static inline size_t GetMaxAllocationSize()
		{
			return (std::numeric_limits<size_t>::max)();
		}
	//private:
	//	// No instantiation
	//	HrNedPoolingPolicy()
	//	{}
	};

	/** An allocation policy for use with AllocatedObject and
	STLAllocator, which aligns memory at a given boundary (which should be
	a power of 2). This is the class that actually does the allocation
	and deallocation of physical memory, and is what you will want to
	provide a custom version of if you wish to change how memory is allocated.
	@par
	This allocation policy uses nedmalloc
	(http://nedprod.com/programs/portable/nedmalloc/index.html).
	@note
	template parameter Alignment equal to zero means use default
	platform dependent alignment.
	*/
	template <size_t Alignment = 0>
	class HrNedPoolingAlignedPolicy
	{
	public:
		// compile-time check alignment is available.
		typedef int IsValidAlignment
			[Alignment <= 128 && ((Alignment & (Alignment - 1)) == 0) ? +1 : -1];

		static inline void* AllocateBytes(size_t count, const char* file = 0, int line = 0, const char* func = 0)
		{
			return HrNedPoolingImpl::AllocBytesAligned(Alignment, count, file, line, func);
		}

		static inline void DeallocateBytes(void* ptr)
		{
			HrNedPoolingImpl::DeallocBytesAligned(Alignment, ptr);
		}

		/// Get the maximum size of a single allocation
		static inline size_t GetMaxAllocationSize()
		{
			return (std::numeric_limits<size_t>::max)();
		}

	//private:
	//	HrNedPoolingAlignedPolicy()
	//	{}
	};

#endif
}

#endif

