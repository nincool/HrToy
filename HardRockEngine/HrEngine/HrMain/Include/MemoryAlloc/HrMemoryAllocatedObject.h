/*
-----------------------------------------------------------------------------
This source file is part of HrEngine
Inspired by Ogre link :http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/


#ifndef _HR_MEMORYALLOCATEOBJECT_H_
#define _HR_MEMORYALLOCATEOBJECT_H_

#include "HrMain/Include/HrMainPrerequisiters.h"

// Anything that has done a #define new <blah> will screw operator new definitions up
// so undefine
#ifdef new
#  undef new
#endif
#ifdef delete
#  undef delete
#endif

namespace Hr
{
	template <class Alloc>
	class HR_MAIN_API HrAllocatedObject
	{
	public:
		HrAllocatedObject(){};
		virtual ~HrAllocatedObject(){};

		/// operator new, with debug line info
		void* operator new(size_t sz, const char* file, int line, const char* func)
		{
			return Alloc::AllocateBytes(sz, file, line, func);
		}

		void* operator new(size_t sz)
		{
			return Alloc::AllocateBytes(sz);
		}

		/// placement operator new
		void* operator new(size_t sz, void* ptr)
		{
			(void)sz;
			return ptr;
		}

		/// array operator new, with debug line info
		void* operator new[](size_t sz, const char* file, int line, const char* func)
		{
			return Alloc::AllocateBytes(sz, file, line, func);
		}

		void* operator new[](size_t sz)
		{
			return Alloc::AllocateBytes(sz);
		}

		void operator delete(void* ptr)
		{
			Alloc::DeallocateBytes(ptr);
		}

		// Corresponding operator for placement delete (second param same as the first)
		void operator delete(void* ptr, void*)
		{
			Alloc::DeallocateBytes(ptr);
		}

		// only called if there is an exception in corresponding 'new'
		void operator delete(void* ptr, const char*, int, const char*)
		{
			Alloc::DeallocateBytes(ptr);
		}

		void operator delete[](void* ptr)
		{
			Alloc::DeallocateBytes(ptr);
		}


		void operator delete[](void* ptr, const char*, int, const char*)
		{
			Alloc::DeallocateBytes(ptr);
		}
	};
}

#endif

