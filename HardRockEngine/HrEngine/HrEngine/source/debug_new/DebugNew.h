//////////////////////////////////////////////////////////////////////////////
// Debug handler for new & delete to get more information out of our memory allocation

#ifndef __DEBUGNEW_H__
#define __DEBUGNEW_H__

#include "HrNew.h"

void* operator new(size_t size, const char* file, int line)
{
	void* pRetMemory = nullptr;
	if (size > 0)
	{
		pRetMemory = HrPool::CHrNew::New( size, file, line );
	}

	return pRetMemory;
}
//no matching operator delete found
void operator delete (void* p, const char* file, int line)
{
	
}

void HrDelete( void* pMemory, const char* file, int line )
{
	HrPool::CHrNew::Delete( pMemory );
}

// Use this macro in the place of "new"  
#define HR_NEW(type) new(__FILE__, __LINE__)(type)()
// Use this macro in the place of "new Type(Param1)"  
#define HR_NEW1(type, param1) new(__FILE__, __LINE__)(type)(param1)
// Use this macro in the place of "new Type(Param1, Param2)"
#define HR_NEW2(type, param1, param2) new(__FILE__, __LINE__)(type)(param1, param2)

#define HR_DELETE(p) HrDelete(p, __FILE__, __LINE__)
//
//#ifdef _DEBUG
//
//// Use this macro in the place of "new"  
//#define HR_NEW(type) debug_new_fn(__FILE__, __LINE__)<type>(); dump_debug_info_new(__FILE__, __LINE__, sizeof(type))
////#define debug_new(type) debug_new_fn<type >(); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
//// Use this macro in the place of "new[]"  (Or "new[]")
//#define debug_newa(type, count) debug_new_fna<type >(count); dump_debug_info_new(__FILE__,__LINE__, sizeof(type) * (count))
//// Use this macro in the place of "new CType(Param)"
//#define debug_new1(type, param1) debug_new_fn_param<type >(param1); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
//// Use this macro in the place of "new CType(Param1, Param2)"
//#define debug_new2(type, param1, param2) debug_new_fn_param<type >(param1, param2); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
//// Use this macro in the place of "new CType(Param1, Param2, Param3)"
//#define debug_new3(type, param1, param2, param3) debug_new_fn_param<type >(param1, param2, param3); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
//
//
//// Use this macro in the place of "delete"
//#define debug_delete(ptr) debug_delete_fn(ptr); dump_debug_info_delete(__FILE__,__LINE__)
//// Use this macro in the place of "delete[]"
//#define debug_deletea(ptr) debug_delete_fna(ptr); dump_debug_info_delete(__FILE__,__LINE__)
//
//#else // _DEBUG
//#define HR_NEW(type) debug_new_fn()<type>()
////#define debug_new(type) debug_new_fn<type >()
//#define debug_newa(type, count) debug_new_fna<type >(count)
//#define debug_new1(type, param1) debug_new_fn_param<type >(param1)
//#define debug_new2(type, param1, param2) debug_new_fn_param<type >(param1, param2)
//#define debug_new3(type, param1, param2, param3) debug_new_fn_param<type >(param1, param2, param3)
//
//#define debug_delete(ptr) debug_delete_fn(ptr)
//#define debug_deletea(ptr) debug_delete_fna(ptr)
//
//#endif // _DEBUG
//
//#include "DebugNew_impl.h"
//
#endif //__DEBUGNEW_H__