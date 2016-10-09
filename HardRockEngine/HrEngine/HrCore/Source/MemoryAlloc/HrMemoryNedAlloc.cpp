#if HR_MEMORY_ALLOCATOR_STD != HR_MEMORY_ALLOCATOR_STD

#include "MemoryAlloc/HrMemoryNedAlloc.h"

#if HR_MEMORY_ALLOCATOR == HR_MEMORY_ALLOCATOR_NED

#include "MemoryAlloc/HrMemoryTracker.h"
#include "Nedmalloc/nedmalloc.c"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
//HrNedPoolingImpl
//////////////////////////////////////////////////////////////////////////
void* Hr::HrNedPoolingImpl::AllocBytes(size_t count, const char* file, int line, const char* func)
{
	void* ptr = nedalloc::nedmalloc(count);

#ifdef HR_MEMORY_TRACKER
	HrMemoryTracker::Get().RecordDealloc(ptr, count, 0, file, line, func);
#endif // HR_MEMORY_TRACKER

	return ptr;
}

void Hr::HrNedPoolingImpl::DeallocBytes(void* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
#ifdef HR_MEMORY_TRACKER
	HrMemoryTracker::Get().RecordDealloc(ptr);
#endif // HR_MEMORY_TRACKER

	nedalloc::nedfree(ptr);
}

void* Hr::HrNedPoolingImpl::AllocBytesAligned(size_t align, size_t count, const char* file, int line, const char* func)
{
	// default to platform SIMD alignment if none specified
	void* ptr = align ? nedalloc::nedmemalign(align, count)
		: nedalloc::nedmemalign(16, count);

	return ptr;
}

void Hr::HrNedPoolingImpl::DeallocBytesAligned(size_t align, void* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	
	nedalloc::nedfree(ptr);
}
#endif

#endif