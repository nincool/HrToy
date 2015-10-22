/************************************************************************ 
* 
*   @Comment：一个超级简单的对象池
*
*   @Author: Hr  
*   @Date: [4/2/2015 By Hr]
*	
************************************************************************/ 
#ifndef _HR_LISTPOOL_H_
#define _HR_LISTPOOL_H_

#include <list>
#include "HrBaseType.h"
#include "HrDebugNew.h"

#define DEBUG_LIST_POOL

namespace Hr
{
	template<typename T>
	class CHrListPool
	{
	public:
		~CHrListPool();
	public:
		void InitListPool(uint nSize);
		void Release();


		T* GetOneFree();
		void RecycleOne(T* pT);

		uint GetUsedSize();
		uint GetFreeSize();
	private:

#ifdef DEBUG_LIST_POOL
		std::list<T*> m_lisBeUsed;
#endif
		std::list<T*> m_lisFree;
	};

	template<typename T>
	CHrListPool<T>::~CHrListPool()
	{
		Release();
	}

	template<typename T>
	void CHrListPool<T>::Release()
	{
#ifdef DEBUG_LIST_POOL
		if (m_lisBeUsed.size() > 0)
		{
			assert( !"List Pool Destroy Error!" );
		}
		m_lisBeUsed.clear();
#endif
		for (auto t : m_lisFree)
		{
			//HR_DELETE( t );
			delete t;
		}
		m_lisFree.clear();
	}

	template<typename T>
	void CHrListPool<T>::InitListPool( uint nSize )
	{
		for (uint i = 0; i < nSize; ++i)
		{
			T* pT = GetOneFree();
			RecycleOne( pT );
		}
	}

	template<typename T>
	T* CHrListPool<T>::GetOneFree()
	{
		T* pT = nullptr;
		if (m_lisFree.empty())
		{
			//只提供默认构造函数
			//pT = HR_NEW( T );
			pT = new T();
		}
		else
		{
		    pT = m_lisFree.back();
			m_lisFree.pop_back();
		}
#ifdef DEBUG_LIST_POOL
		m_lisBeUsed.push_back( pT );
#endif

		return pT;
	}

	template<typename T>
	void CHrListPool<T>::RecycleOne( T* pT )
	{
		if (pT != nullptr)
		{
#ifdef DEBUG_LIST_POOL
			auto findItem = find(m_lisBeUsed.begin(), m_lisBeUsed.end(), pT);
			if (findItem == m_lisBeUsed.end())
			{
				assert( !"The Obj is not in the list pool!" );
				return;
			}
			else
			{
				m_lisBeUsed.erase( findItem );
			}
#endif
			m_lisFree.push_back( pT );
		}
	}

	template<typename T>
	uint CHrListPool<T>::GetUsedSize()
	{
		return m_lisBeUsed.size();
	}

	template<typename T>
	uint CHrListPool<T>::GetFreeSize()
	{
		return m_lisFree.size();
	}
}

#endif


