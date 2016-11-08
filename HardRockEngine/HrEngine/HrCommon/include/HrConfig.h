/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [11/6/2015 By Hr]
*
************************************************************************/  
#ifndef __HR_CONFIG_H__
#define __HR_CONFIG_H__

// define the memory allocator configuration to use
#define HR_MEMORY_ALLOCATOR_STD 1
#define HR_MEMORY_ALLOCATOR_NED 2
#define HR_MEMORY_ALLOCATOR_USER 3
#define HR_MEMORY_ALLOCATOR_NEDPOOLING 4

#ifndef HR_MEMORY_ALLOCATOR
#  define HR_MEMORY_ALLOCATOR HR_MEMORY_ALLOCATOR_STD
#endif

#define HR_MEMORY_TRACKER

#pragma warning(disable: 4251) // STL classes are not dllexport.
#pragma warning(disable: 4275) // Derived from non dllexport classes.
#pragma warning(disable: 4503) // Some decorated name in boost are very long.
#pragma warning(disable: 4819) // Allow non-ANSI characters. 
#pragma warning(disable: 4521) // multiple copy constructors specified.

//#define BOOST_DISABLE_ASSERTS
#include <boost/assert.hpp>

#endif //__HR_CONFIG_H__



