#pragma once
#include "HrMemoryBase.h"
#include <memory>

namespace HrPool
{
#define HR_MEMORY_BLOCK_INFO_MAX_SIZE    124
#define HR_MEMORY_REGISTER_MAX           10000

	struct SHrMemoryRegister
	{
		void*     m_pMemory;
		char      m_szInfo[HR_MEMORY_BLOCK_INFO_MAX_SIZE];
	};

	class CHrLowDebug;
	class CHrMemoryRegister
	{
	public:
		CHrMemoryRegister( CHrLowDebug* pDebugLog );
		~CHrMemoryRegister();
	
	public:
		/**
		 *	@Comment: 添加内存注册信息 [3/6/2015 By Hr]
		 *	@Param:   pMemory:内存块指针 szInfo:注册信息
		 *	@Return:  void
		*/
		void         Add( void* pMemory, char* szInfo );
		/**
		 *	@Comment: 删除某内存块注册信息 [3/6/2015 By Hr]
		 *	@Param:   pMemory:内存块指针
		*/
		void         Del( void* pMemory );
		/**
		 *	@Comment: 修改内存块 [3/6/2015 By Hr]
		*/
		void         Modify( void* pOld, void* pNew );
		/**
		 *	@Brief: 打印信息 [3/6/2015 By Hr]
		*/
		void         PrintInfo();
	private:
		void         RegisterCopy( SHrMemoryRegister* pDest, void* pMemory, char* szInfo );
	private:
		CHrLowDebug*        m_pDebugLog;

		SHrMemoryRegister   m_registerArr[HR_MEMORY_REGISTER_MAX];

		//最大使用节点数
		int                 m_nUsedMax;
		//当前地址的最大值 
		void*               m_pMaxMemoryAddress;
		//保存了多少内存有效地址
		int                 m_nMemoryAddressCount;
	};
}






