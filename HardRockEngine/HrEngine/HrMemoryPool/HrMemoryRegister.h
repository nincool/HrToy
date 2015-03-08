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
		 *	@Comment: ����ڴ�ע����Ϣ [3/6/2015 By Hr]
		 *	@Param:   pMemory:�ڴ��ָ�� szInfo:ע����Ϣ
		 *	@Return:  void
		*/
		void         Add( void* pMemory, char* szInfo );
		/**
		 *	@Comment: ɾ��ĳ�ڴ��ע����Ϣ [3/6/2015 By Hr]
		 *	@Param:   pMemory:�ڴ��ָ��
		*/
		void         Del( void* pMemory );
		/**
		 *	@Comment: �޸��ڴ�� [3/6/2015 By Hr]
		*/
		void         Modify( void* pOld, void* pNew );
		/**
		 *	@Brief: ��ӡ��Ϣ [3/6/2015 By Hr]
		*/
		void         PrintInfo();
	private:
		void         RegisterCopy( SHrMemoryRegister* pDest, void* pMemory, char* szInfo );
	private:
		CHrLowDebug*        m_pDebugLog;

		SHrMemoryRegister   m_registerArr[HR_MEMORY_REGISTER_MAX];

		//���ʹ�ýڵ���
		int                 m_nUsedMax;
		//��ǰ��ַ�����ֵ 
		void*               m_pMaxMemoryAddress;
		//�����˶����ڴ���Ч��ַ
		int                 m_nMemoryAddressCount;
	};
}






