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
		 *	@Comment: ������Դ [3/6/2015 By Hr]
		 *	@Param:   nSize:�����ڴ�Ĵ�С
		*/
		void*				Mallock( size_t nSize );
		/**
		 *	@Comment: �ͷ���Դ [3/6/2015 By Hr]
		*/
		bool                Free( void* pMemory );

		/**
		 *	@Comment: ��ӡ���ٵĶ�����Ϣ [3/8/2015 By Hr]
		*/
		void                PrintStack();
		/**
		 *	@Comment: ��ӡ���ٵ��ڴ���Ϣ [3/8/2015 By Hr]
		*/
		void                PrintInfo();
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


