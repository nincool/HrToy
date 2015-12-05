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
#  define HR_MEMORY_ALLOCATOR HR_MEMORY_ALLOCATOR_NEDPOOLING
#endif

#define HR_MEMORY_TRACKER

#endif //__HR_CONFIG_H__



