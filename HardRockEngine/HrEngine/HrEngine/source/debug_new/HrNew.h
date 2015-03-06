#pragma once
#include "HrPoolManager.h"
#include <memory>

namespace HrPool
{
	class CHrNew
	{
	public:
		CHrNew();
		~CHrNew();

	public:
		static void* New(size_t nSize, const char* file, int line)
		{
			void* pRetMemory = m_s_pPoolManager->Malloc( nSize );
			return pRetMemory;
		}

		static void Delete( void* pMemory )
		{
			m_s_pPoolManager->Free( pMemory );
		}
	private:
		static std::shared_ptr<CHrPoolManager> m_s_pPoolManager;
	};
}


