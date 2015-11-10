/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [11/6/2015 By Hr]
*
************************************************************************/  
#ifndef __HR_DEBUGNEW_H__
#define __HR_DEBUGNEW_H__

inline void* operator new(size_t size, const char* file, int line)
{
	return nullptr;
}
//no matching operator delete found
inline void operator delete (void* p, const char* file, int line)
{
}

// Use this macro in the place of "new"  
//#define HR_NEW(type) new(__FILE__, __LINE__)(type)()
#define HNEW(type) new (type)()
// Use this macro in the place of "new Type(Param1)"  
//#define HNEW1(type, param1) new(__FILE__, __LINE__)(type)(param1)
#define HNEW1(type, param1) new (type)(param1)
// Use this macro in the place of "new Type(Param1, Param2)"
//#define HNEW2(type, param1, param2) new(__FILE__, __LINE__)(type)(param1, param2)
#define HNEW2(type, param1, param2) new (type)(param1, param2)
//#define HR_DELETE(p) HrDelete(p, __FILE__, __LINE__)
#define HDELETE(p) if (p) { delete p; p = nullptr;}


#endif //__DEBUGNEW_H__



