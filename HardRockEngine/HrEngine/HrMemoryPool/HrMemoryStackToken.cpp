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
		//�ж��Ƿ��п��İ����ڴ�鱸��
		if (m_pFirstSon == nullptr)
		{
			//���û�� ��Ҫ��ϵͳ��������һ���ڴ��
			pNewMemory = (SHrMemBlockHead*)malloc( m_nBlockSize );
			if (pNewMemory != NULL)
			{
				//ͳ�ƺ��� +1
				//��Ϊ����ڴ�����Ͼͻ�����ȥ �޶�m_uBlockOutSide + 1 InSide ����
				++m_nBlockOutSide;
				nMemoryUse += m_nBlockSize;

				//��ʼ����������ڴ�� ����С��Ϣ
				pNewMemory->m_nBlockSize = m_nBlockSize;
				pNewMemory->m_pNext = nullptr;
				pRetMemory = HR_MEM_BLOCK_DATA( pNewMemory );

				//ͳ�Ʊ��� �ڴ������ +1
				++nAllBlockCount;
			}
			else
			{
				/*
				* ---- ����ʧ�� by Hr 2/18/2013------
				*/
				m_pDebugLog->Debug2File( "HrMemoryStackToken Malloc Error!!! m_nBlockSize[%d]", m_nBlockSize );
				assert( m_nBlockSize &&  "HrMemoryStackToken Malloc Error!!" );
			}
		}
		else
		{
			//�����п����ڴ������
			//ֱ����ȡ�����һ�� Ҳ����ջ�����¼�����ڴ��
			pNewMemory = m_pFirstSon;
			m_pFirstSon = pNewMemory->m_pNext;
			pNewMemory->m_pNext = nullptr;
			pRetMemory = HR_MEM_BLOCK_DATA( pNewMemory );

			//���ڲ����ڴ�������·���
			++m_nBlockOutSide;
			--m_nBlockInSide;
		}
	}
	else
	{
		//����ߴ粻�������� �����ֵܽڵ㴦�� �ڴ���֮ǰ �ȼ�鲢�����ֵܽڵ�

		//����ֵܽڵ��Ƿ��Ѿ����� ���û�д��� ��ô����
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

	//�ж��ڴ���Ƿ�Խ ����������� ֱ���ͷ� �������ô���
	if (HR_MEM_BLOCK_MAX_SAVE_BLOCK_SIZE <= m_nBlockSize)
	{
		free( pOld );
		bRetVal = true;

		return bRetVal;
	}

	//���ȼ���ڴ��Ĵ�С�Ƿ��ɱ��������
	if (m_nBlockSize == pOld->m_nBlockSize)
	{
		if (bCloseFlag)
		{
			//ֱ���ͷ�
			free( pOld );
			--m_nBlockOutSide;
		}
		else
		{
			//���������������� ����������֦ջ ׼�������ڴ�ջ
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
	//�ݻ����е��ӽڵ�
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




