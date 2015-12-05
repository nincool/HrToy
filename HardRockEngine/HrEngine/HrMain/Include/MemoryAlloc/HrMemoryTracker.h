/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [12/3/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_MEMORYTRACKER_H_
#define _HR_MEMORYTRACKER_H_

#include <string>
#include <unordered_map>
#include <mutex>

namespace Hr
{
	class HrMemoryTracker
	{
	public:
		HrMemoryTracker();
		~HrMemoryTracker();
		
	public:

		/** Record an allocation that has been made. Only to be called by
		the memory management subsystem.
		@param ptr The pointer to the memory
		@param sz The size of the memory in bytes
		@param pool The memory pool this allocation is occurring from
		@param file The file in which the allocation is being made
		@param ln The line on which the allocation is being made
		@param func The function in which the allocation is being made
		*/
		void RecordDealloc(void* ptr, size_t sz, unsigned int pool = 0, const char* file = 0, size_t ln = 0, const char* func = 0);
		/** Record the deallocation of memory. */
		void RecordDealloc(void* ptr);

		/// Static utility method to get the memory tracker instance
		static HrMemoryTracker& Get();
	protected:
		std::mutex mtx;

		// Allocation record
		struct Alloc
		{
			size_t bytes;
			unsigned int pool;
			std::string filename;
			size_t line;
			std::string function;

			Alloc() :bytes(0), line(0) {}
			Alloc(size_t sz, unsigned int p, const char* file, size_t ln, const char* func)
				:bytes(sz), pool(p), line(ln)
			{
				if (file)
					filename = file;
				if (func)
					function = func;
			}
		};
		std::string m_strLeakFileName;
		bool m_bDumpToStdOut;
		std::unordered_map<void*, Alloc> m_Allocations;

		size_t m_nTotalAllocations;
		std::vector<size_t> m_vecAllocationsByPool;
		bool m_bRecordEnable;

		void ReportLeaks();
	};
}


#endif

