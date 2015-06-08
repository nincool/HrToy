#pragma once
#include "HrMemoryDllDef.h"
#include <list>

namespace HrPool
{
	class CHrLowDebug;
	class CHrMemoryStack;
	class CHrMemoryRegister;
	class CHrPoolListener;
	class HR_MEMORY_DLL CHrPoolManager
	{
	public:
		CHrPoolManager(bool bOpenRegister = false);
		~CHrPoolManager();

	public:

		/**
		 *	@Brief: 分配内存 [3/5/2015 By Hr]
		*/
		void*		Malloc( size_t nSize, char* szInfo = nullptr );
		/**
		 *	@Brief: 释放内存 [3/5/2015 By Hr]
		*/
		void        Free( void* pMemory );


		void        PrintTree();
		void        PrintInfo();

		void        Release();

		void        RegisterPoolListener(CHrPoolListener* pListener)
		{
			if (pListener != nullptr)
			{
				m_lisPoolListener.push_back(pListener);
			}
		}

	private:
		void        RegisterMemoryInfo( void* pMemory, char* szInfo );
		void        UnRegisterMemoryInfo( void* pMemory );
	private:
		CHrLowDebug*        m_pDebugLog;

		CHrMemoryRegister*  m_pRegister;

		CHrMemoryStack*     m_pMemoryStack;

		std::list<CHrPoolListener*> m_lisPoolListener;
	};
}


