#include "stdafx.h"
#include "HrMemoryStackToken.h"
#include "malloc.h"
#include "HrLowDebug.h"

using namespace HrPool;
CHrMemoryStackToken::CHrMemoryStackToken( int nBlockSize, CHrLowDebug* pDebugLog )
{
	m_pDebugLog = pDebugLog;

	m_nBlockInSide = 0;
	m_nBlockOutSide = 0;
	m_nBlockSize = nBlockSize;

	m_pFirstSon = nullptr;
	m_pNext = nullptr;
}

CHrMemoryStackToken::~CHrMemoryStackToken()
{
	if (m_nBlockOutSide != 0)
	{
		if (m_pDebugLog != nullptr)
		{
			m_pDebugLog->Debug2File( "Hr Memory Stack:lost:%d * %d\n", m_nBlockSize, m_nBlockOutSide );
		}
	}

	if (m_pFirstSon != nullptr)
	{
		DestroySon( m_pFirstSon );
	}
	m_pFirstSon = nullptr;
	if (m_pNext != nullptr)
	{
		delete m_pNext;
		m_pNext = nullptr;
	}
}

void* CHrMemoryStackToken::Malloc( size_t nSize, uint& nAllBlockCount, uint& nMemoryUse )
{
	void* pRetMemory = nullptr;
	SHrMemBlockHead* pNewMemory = nullptr;

	if (nSize >= HR_MEM_BLOCK_MAX_SAVE_BLOCK_SIZE)
	{
		void* pTempMemory = malloc( nSize );
		if (pTempMemory != NULL)
		{
			return pTempMemory;
		}
		else
		{
			m_pDebugLog->Debug2File( "HrMemoryStackToken Malloc Error without memory pool!!! nSize[%d]", nSize );
		}
	}

	if (HR_MEM_BLOCK_SIZE( nSize ) < m_nBlockSize)
	{
		//判断是否有空心啊的内存块备用
		if (m_pFirstSon == nullptr)
		{
			//如果没有 需要向系统重新申请一个内存块
			pNewMemory = (SHrMemBlockHead*)malloc( m_nBlockSize );
			if (pNewMemory != NULL)
			{
				//统计函数 +1
				//因为这个内存块马上就会分配出去 修订m_uBlockOutSide + 1 InSide 不加
				++m_nBlockOutSide;
				nMemoryUse += m_nBlockSize;

				//初始化新申请的内存块 填充大小信息
				pNewMemory->m_nBlockSize = m_nBlockSize;
				pNewMemory->m_pNext = nullptr;
				pRetMemory = HR_MEM_BLOCK_DATA( pNewMemory );

				//统计变量 内存块总数 +1
				++nAllBlockCount;
			}
			else
			{
				/*
				* ---- 分配失败 by Hr 2/18/2013------
				*/
				m_pDebugLog->Debug2File( "HrMemoryStackToken Malloc Error!!! m_nBlockSize[%d]", m_nBlockSize );
				assert( m_nBlockSize &&  "HrMemoryStackToken Malloc Error!!" );
			}
		}
		else
		{
			//这是有空闲内存块的情况
			//直接提取链表第一块 也就是栈上最新加入的内存块
			pNewMemory = m_pFirstSon;
			m_pFirstSon = pNewMemory->m_pNext;
			pNewMemory->m_pNext = nullptr;
			pRetMemory = HR_MEM_BLOCK_DATA( pNewMemory );

			//把内部的内存块再重新分配
			++m_nBlockOutSide;
			--m_nBlockInSide;
		}
	}
	else
	{
		//本类尺寸不符合需求 该由兄弟节点处理 在处理之前 先检查并生成兄弟节点

		//检查兄弟节点是否已经创建 如果没有创建 那么创建
		if (m_pNext == nullptr)
		{
			m_pNext = new CHrMemoryStackToken( m_nBlockSize * 2, m_pDebugLog );
		}
		if (m_pNext != nullptr)
		{
			pRetMemory = m_pNext->Malloc( nSize, nAllBlockCount, nMemoryUse );
		}
	}

	return pRetMemory;
}

bool CHrMemoryStackToken::Free( void* pMemory, bool bCloseFlag )
{
	bool bRetVal = false;

	SHrMemBlockHead* pOld = HR_MEM_BLOCK_HEAD( pMemory );

	//判断内存块是否超越 如果超出限制 直接释放 不做重用处理
	if (HR_MEM_BLOCK_MAX_SAVE_BLOCK_SIZE <= m_nBlockSize)
	{
		free( pOld );
		bRetVal = true;

		return bRetVal;
	}

	//首先检查内存块的大小是否由本对象管理
	if (m_nBlockSize == pOld->m_nBlockSize)
	{
		if (bCloseFlag)
		{
			//直接释放
			free( pOld );
			--m_nBlockOutSide;
		}
		else
		{
			//当所有条件不满足 正常推入右枝栈 准备重用内存栈
			pOld->m_pNext = m_pFirstSon;
			m_pFirstSon = pOld;

			--m_nBlockOutSide;
			++m_nBlockInSide;
		}
		bRetVal = true;
	}
	else
	{
		if (m_pNext != nullptr)
		{
			bRetVal = m_pNext->Free( pMemory, bCloseFlag );
		}
	}

	return bRetVal;
}

void CHrMemoryStackToken::PrintStack()
{
	if (m_nBlockInSide + m_nBlockOutSide > 0)
	{
		m_pDebugLog->Debug2File( " [%ld]stack:all=%d, out=%d, in=%d\n"
			, m_nBlockSize, m_nBlockInSide + m_nBlockOutSide
			, m_nBlockOutSide
			, m_nBlockInSide );

	}
	if (m_pNext != nullptr)
	{
		m_pNext->PrintStack();
	}
}

void HrPool::CHrMemoryStackToken::DestroySon( SHrMemBlockHead* pSon )
{
	//摧毁所有的子节点
	SHrMemBlockHead* pObjNow = pSon;
	SHrMemBlockHead* pObjNext = nullptr;

	while (true)
	{
		if (pObjNow == nullptr)
		{
			break;
		}
		pObjNext = pObjNow->m_pNext;
		free( pObjNow );
		--m_nBlockInSide;
		pObjNow = pObjNext;
	}
}




