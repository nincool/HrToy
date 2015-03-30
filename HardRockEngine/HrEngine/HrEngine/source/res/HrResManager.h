#ifndef _HR_RESMANAGER_H_
#define _HR_RESMANAGER_H_

#include "HrEngineCom.h"
#include <unordered_map>
#include "HrBaseRes.h"

namespace Hr
{
	class CHrResManager
	{
	public:
		CHrResManager();
		virtual ~CHrResManager();

		typedef uint RESHANDLE;
		typedef std::unordered_map<int, CHrBaseRes*> UMAP;
		typedef std::unordered_map<int, CHrBaseRes*>::iterator UMAPItor;
	public:
		void Clear();
		
		bool Create(uint nMaxSize);
		
		void Destroy();

		//--------------------------------------------------------------------
		//��Դӳ����ʽ
		inline void GotoBegin()
		{
			m_currentRes = m_mapRes.begin();
		}
		inline CHrBaseRes* GetCurrentResource()
		{
			return (m_currentRes->second);
		}
		inline bool GotoNext()
		{
			++m_currentRes;
			return IsValid();
		}
		inline bool IsValid()
		{
			return (m_currentRes != m_mapRes.end()) ? true : false;
		}

		//-----------------------------------------------------------------------
		//һ����Դ����
		bool ReserveMemory( size_t nMem );

		bool InsertResource( RESHANDLE* pRhUniqueID, CHrBaseRes* pResource );
		bool InsertResource( RESHANDLE rhUniqueID, CHrBaseRes* pResource );

		//�ӹ���������ȫɾ��һ������ 
		bool RemoveResource( CHrBaseRes* pResource );
		bool RemoveResource( RESHANDLE rhUniqueID );
	
		//����һ�������ͷ����ڴ�
		bool DestroyResource( CHrBaseRes* pResource );
		bool DestroyResource( RESHANDLE rhUniqueID );

		//ʹ��GetResource���ʶ���
		//�����Դ�Ѿ����ͷţ������ڱ�����֮ǰ�ؽ�
		CHrBaseRes* GetResource( RESHANDLE rhUniquiID );

		//������Դ��ȷ����Դ���ᱻ��Դ����������
		//�����ʹ�����������ȷ��һ����Դ��ʵ�������������ڴ�
		//��Դ����һ�����ü�������ȷ���ܰ�ȫ�ı�����������
		CHrBaseRes* Lock( RESHANDLE rhUniqueID );

		int Unlock( RESHANDLE rhUniqueID );
		int Unlock( CHrBaseRes* pResource );

		//������Դָ���ȡ�洢���
		RESHANDLE FindResourceHandle( CHrBaseRes* pResource );

	protected:
		inline void AddMemory( uint nMem )
		{
			m_nCurrentUsedMemory += nMem;
		}
		inline void RemoveMemory( uint nMem )
		{
			m_nCurrentUsedMemory -= nMem;
		}
		RESHANDLE GetNextResHandle()
		{
			return m_rhNextResHandle;
		}
	protected:
		RESHANDLE m_rhNextResHandle;
		uint      m_nCurrentUsedMemory;
		uint      m_nMaximumMemory;

		UMAPItor  m_currentRes;

		UMAP      m_mapRes;
	};

}


#endif


