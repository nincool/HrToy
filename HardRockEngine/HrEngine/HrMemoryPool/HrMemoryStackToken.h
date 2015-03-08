#pragma once
#include "HrMemoryBase.h"
#include <memory>

namespace HrPool
{

#define HR_MEM_BLOCK_SIZE(nDataLength)			(nDataLength + g_nHrMemoryBlockHeadSize)
#define HR_MEM_BLOCK_DATA_SIZE(nBlockSize)		(nBlockSize - g_nHrMemoryBlockHeadSize)
#define HR_MEM_BLOCK_HEAD(pData)                ((SHrMemBlockHead*)(((char*)pData) - g_nHrMemoryBlockHeadSize))
#define HR_MEM_BLOCK_DATA(pHead)				(((char*)pHead) + g_nHrMemoryBlockHeadSize)
#define HR_MEM_BLOCK_MIN						16
#define HR_MEM_BLOCK_MAX_SAVE_BLOCK_SIZE		(1 * 1024 * 1024)

	struct SHrMemBlockHead
	{
		//模块大小
		uint				m_nBlockSize;
		SHrMemBlockHead*        m_pNext;
	};
	const uint g_nHrMemoryBlockHeadSize = sizeof( SHrMemBlockHead );

	class CHrLowDebug;
	class CHrMemoryStackToken
	{
	public:
		CHrMemoryStackToken( int nBlockSize, CHrLowDebug* pDebugLog );
		~CHrMemoryStackToken();

	public:
		/**
		 *	@Brief: 基本的申请函数，返回成功申请的内存块指针 [3/4/2015 By Hr]
		*/
		void*		Malloc( int nSize, uint& nAllBlockCount, uint& nMemoryUse );
		/*
		@brief:   	释放函数 bClose是一个特殊的优化，即在程序退出是释放内存不会再返回内存栈 直接free掉 加快程序退出速度 by Hr 2/17/2013
					应用程序传进来的是p1, 内部需要逆向计算出p0实现操作
		*/
		bool        Free( void* pMemory, bool bCloseFlag );

		/*
		@brief:   	观察函数 by Hr 2/17/2013
		*/
		void		PrintStack();

	private:
		/*
		@brief:   	系统退出 递归销毁所有内存块函数 by Hr 2/17/2013
		*/
		void		DestroySon( SHrMemBlockHead* pSon );
	private:
		CHrLowDebug*           m_pDebugLog;
		
		//链头
		SHrMemBlockHead*       m_pFirstSon; 
		//左支下一节点的指针
		CHrMemoryStackToken*   m_pNext;

		//管理的内存块尺寸 
		uint                   m_nBlockSize;
		//分配出去的内存块数量
		uint                   m_nBlockOutSide;
		//内部保留的空闲内存
		uint                   m_nBlockInSide;
	};
}





