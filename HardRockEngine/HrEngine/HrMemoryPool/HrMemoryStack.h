#pragma once
#include "HrMemoryBase.h"
#include <memory>

namespace HrPool
{
	class CHrLowDebug;
	class CHrMemoryStackToken;
	class CHrMemoryStack
	{
	public:
		CHrMemoryStack( CHrLowDebug* pDebugLog );
		~CHrMemoryStack();

	public:
		/**
		 *	@Comment: 申请资源 [3/6/2015 By Hr]
		 *	@Param:   nSize:申请内存的大小
		*/
		void*				Mallock( size_t nSize );
		/**
		 *	@Comment: 释放资源 [3/6/2015 By Hr]
		*/
		bool                Free( void* pMemory );

		/**
		 *	@Comment: 打印开辟的队列信息 [3/8/2015 By Hr]
		*/
		void                PrintStack();
		/**
		 *	@Comment: 打印开辟的内存信息 [3/8/2015 By Hr]
		*/
		void                PrintInfo();
	private:
		CHrLowDebug*		m_pDebugLog;

		CHrMemoryStackToken* m_pStackTokenHead;
		//内存的最大地址
		uint64               m_nMaxMemoryAddress;
		//开辟了多少内存块
		uint                m_nAllBlockCount;
		//一共有多少内存在使用
		uint                m_nMemoryUsed;
		bool                m_bCloseFlag;
	};
}


