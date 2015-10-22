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

		static void DestoryMemoryManager()
		{
			m_s_pPoolManager.reset();
		}

		static void PrintMemoryInfo()
		{
			m_s_pPoolManager->PrintInfo();
			m_s_pPoolManager->PrintTree();
		}

		static void RegistListener(CHrPoolListener* pListener)
		{
			if (pListener != nullptr)
			{
				if (m_s_pPoolManager)
					m_s_pPoolManager->RegisterPoolListener(pListener);
			}

		}
		static void UnRegisteListener(CHrPoolListener* pListener)
		{
			if (pListener != nullptr)
				if (m_s_pPoolManager)
					m_s_pPoolManager->UnRegistePoolListener(pListener);
		}
	private:
		static std::shared_ptr<CHrPoolManager> m_s_pPoolManager;
	};
}


