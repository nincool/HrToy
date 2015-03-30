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
		//资源映射表达式
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
		//一般资源访问
		bool ReserveMemory( size_t nMem );

		bool InsertResource( RESHANDLE* pRhUniqueID, CHrBaseRes* pResource );
		bool InsertResource( RESHANDLE rhUniqueID, CHrBaseRes* pResource );

		//从管理器中完全删除一个对象 
		bool RemoveResource( CHrBaseRes* pResource );
		bool RemoveResource( RESHANDLE rhUniqueID );
	
		//析构一个对象并释放其内存
		bool DestroyResource( CHrBaseRes* pResource );
		bool DestroyResource( RESHANDLE rhUniqueID );

		//使用GetResource访问对象
		//如果资源已经被释放，它将在被返回之前重建
		CHrBaseRes* GetResource( RESHANDLE rhUniquiID );

		//锁定资源以确保资源不会被资源管理器管理
		//你可以使用这个函数来确保一个资源的实力不被交换出内存
		//资源包括一个引用技术器来确保能安全的保存锁的数量
		CHrBaseRes* Lock( RESHANDLE rhUniqueID );

		int Unlock( RESHANDLE rhUniqueID );
		int Unlock( CHrBaseRes* pResource );

		//基于资源指针获取存储句柄
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


