//////////////////////////////////////////////////////////////////////////////
// Debug new handler implementation
#ifdef _DEBUG

#include <windows.h>
#include <stdio.h>



static int g_nDebugAlloc_AllocCount = 0;

void dump_debug_info_new(const char *pFile, unsigned int nLine, unsigned int nSize)
{
	// Count the allocation
	++g_nDebugAlloc_AllocCount;

}

void dump_debug_info_delete(const char *pFile, unsigned int nLine)
{
	// Count the deallocation
	--g_nDebugAlloc_AllocCount;

}

#endif // _DEBUG