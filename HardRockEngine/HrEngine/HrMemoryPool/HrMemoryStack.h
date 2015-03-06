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
		CHrMemoryStack(std::shared_ptr<CHrLowDebug>& pDebugLog);
		~CHrMemoryStack();

	public:
		/**
		 *	@Comment: ������Դ [3/6/2015 By Hr]
		 *	@Param:   nSize:�����ڴ�Ĵ�С
		*/
		void*				Mallock( int nSize );
		/**
		 *	@Comment: �ͷ���Դ [3/6/2015 By Hr]
		*/
		bool                Free( void* pMemory );
	private:
		CHrLowDebug*		m_pDebugLog;

		CHrMemoryStackToken* m_pStackTokenHead;
		//�ڴ������ַ
		uint64               m_nMaxMemoryAddress;
		//�����˶����ڴ��
		uint                m_nAllBlockCount;
		//һ���ж����ڴ���ʹ��
		uint                m_nMemoryUsed;
		bool                m_bCloseFlag;
	};
}


