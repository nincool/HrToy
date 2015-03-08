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
		//ģ���С
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
		 *	@Brief: ���������뺯�������سɹ�������ڴ��ָ�� [3/4/2015 By Hr]
		*/
		void*		Malloc( int nSize, uint& nAllBlockCount, uint& nMemoryUse );
		/*
		@brief:   	�ͷź��� bClose��һ��������Ż������ڳ����˳����ͷ��ڴ治���ٷ����ڴ�ջ ֱ��free�� �ӿ�����˳��ٶ� by Hr 2/17/2013
					Ӧ�ó��򴫽�������p1, �ڲ���Ҫ��������p0ʵ�ֲ���
		*/
		bool        Free( void* pMemory, bool bCloseFlag );

		/*
		@brief:   	�۲캯�� by Hr 2/17/2013
		*/
		void		PrintStack();

	private:
		/*
		@brief:   	ϵͳ�˳� �ݹ����������ڴ�麯�� by Hr 2/17/2013
		*/
		void		DestroySon( SHrMemBlockHead* pSon );
	private:
		CHrLowDebug*           m_pDebugLog;
		
		//��ͷ
		SHrMemBlockHead*       m_pFirstSon; 
		//��֧��һ�ڵ��ָ��
		CHrMemoryStackToken*   m_pNext;

		//������ڴ��ߴ� 
		uint                   m_nBlockSize;
		//�����ȥ���ڴ������
		uint                   m_nBlockOutSide;
		//�ڲ������Ŀ����ڴ�
		uint                   m_nBlockInSide;
	};
}





