#if HR_MEMORY_ALLOCATOR_STD != HR_MEMORY_ALLOCATOR_STD

#include "MemoryAlloc/HrMemoryTracker.h"
#include <assert.h>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace Hr;

HrMemoryTracker::HrMemoryTracker() : m_strLeakFileName("HrLeaks.log")
{
	m_bDumpToStdOut = true;
	m_bRecordEnable = true;
	m_nTotalAllocations = 0;
}

HrMemoryTracker::~HrMemoryTracker()
{
	ReportLeaks();
}

HrMemoryTracker& HrMemoryTracker::Get()
{
	static HrMemoryTracker tracker;
	return tracker;
}

void HrMemoryTracker::RecordDealloc(void* ptr, size_t sz, unsigned int pool /*= 0*/, const char* file /*= 0*/, size_t ln /*= 0*/, const char* func /*= 0*/)
{
	if (m_bRecordEnable)
	{
		mtx.lock();
		std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);
		assert(m_Allocations.find(ptr) == m_Allocations.end() && "Double allocation with same address - "
			"this probably means you have a mismatched allocation / deallocation style, "
			"check if you're are using OGRE_ALLOC_T / OGRE_FREE and OGRE_NEW_T / OGRE_DELETE_T consistently");

		m_Allocations[ptr] = Alloc(sz, pool, file, ln, func);
		if (pool >= m_vecAllocationsByPool.size())
		{
			m_vecAllocationsByPool.resize(pool + 1, 0);
		}
		m_vecAllocationsByPool[pool] += sz;
		m_nTotalAllocations += sz;
	}
}

void HrMemoryTracker::RecordDealloc(void* ptr)
{
	if (m_bRecordEnable)
	{
		if (ptr == nullptr)
		{
			return;
		}
		mtx.lock();
		std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);

		std::unordered_map<void*, Alloc>::iterator itr = m_Allocations.find(ptr);
		assert(itr != m_Allocations.end() && "Unable to locate allocation unit - "
			"this probably means you have a mismatched allocation / deallocation style, "
			"check if you're are using OGRE_ALLOC_T / OGRE_FREE and OGRE_NEW_T / OGRE_DELETE_T consistently");
		// update category stats
		m_vecAllocationsByPool[itr->second.pool] -= itr->second.bytes;
		//global stats
		m_nTotalAllocations -= itr->second.bytes;
		m_Allocations.erase(itr);
	}
}

#include <windows.h>

void HrMemoryTracker::ReportLeaks()
{
	if (m_bRecordEnable)
	{
		std::stringstream os;

		if (m_Allocations.empty())
		{
			os << "Hr Memory: No memory leaks" << std::endl;
		}
		else
		{
			os << "Hr Memory: Detected memory leaks !!! " << std::endl;
			os << "Hr Memory: (" << m_Allocations.size() << ") Allocation(s) with total " << m_nTotalAllocations << " bytes." << std::endl;
			os << "Hr Memory: Dumping allocations -> " << std::endl;


			for (std::unordered_map<void*, Alloc>::iterator i = m_Allocations.begin(); i != m_Allocations.end(); ++i)
			{
				const Alloc& alloc = i->second;
				if (!alloc.filename.empty())
					os << alloc.filename;
				else
					os << "(unknown source):";

				os << "(" << alloc.line << ") : {" << alloc.bytes << " bytes}" << " function: " << alloc.function << std::endl;

			}
			os << std::endl;
		}

		std::ofstream of;
		of.open(m_strLeakFileName.c_str());
		of << os.str();
		of.close();
	}
}

#endif


