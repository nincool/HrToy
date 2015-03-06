#pragma once
#include "HrMemoryDllDef.h"
#include <memory>

namespace HrPool
{
	class CHrMemoryStack;
	class CHrLowDebug;
	class CHrMemoryRegister;
	class HR_MEMORY_DLL CHrPoolManager
	{
	public:
		CHrPoolManager(bool bOpenRegister = false);
		~CHrPoolManager();

	public:

		/**
		 *	@Brief: �����ڴ� [3/5/2015 By Hr]
		*/
		void*		Malloc( int nSize, char* szInfo = nullptr );
		/**
		 *	@Brief: �ͷ��ڴ� [3/5/2015 By Hr]
		*/
		void        Free( void* pMemory );

	private:
		void        RegisterMemoryInfo( void* pMemory, char* szInfo );
		void        UnRegisterMemoryInfo( void* pMemory );
	private:
		std::shared_ptr<CHrLowDebug> m_pDebugLog;

		CHrMemoryRegister*  m_pRegister;

		CHrMemoryStack*     m_pMemoryStack;

		
	};
}


