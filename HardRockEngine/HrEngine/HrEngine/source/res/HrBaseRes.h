#ifndef _HR_BASERES_H_
#define _HR_BASERES_H_

#include "HrEngineCom.h"

namespace Hr
{
	class CHrBaseRes
	{
	public:
		CHrBaseRes();
		virtual ~CHrBaseRes();

	public:
		enum _PRIORITY_TYPE_
		{
			RES_LOW_PRIORITY = 0,
			RES_MED_PRIORITY,
			RES_HIGH_PRIORITY
		};

		virtual void Clear(){};

		virtual bool Create(){ return false; }
		virtual void Destroy(){}

		virtual bool Recreate() = 0;
		virtual void Dispose() = 0;

		virtual size_t GetSize() = 0;
		virtual bool IsDisposed() = 0;

		inline void setPriority( _PRIORITY_TYPE_ priority )
		{
			m_Priority = priority;
		}
		inline _PRIORITY_TYPE_ GetPriority()
		{
			return m_Priority;
		}

		inline void SetReferenceCount( uint nCount )
		{
			m_nRefCount = nCount;
		}
		inline uint GetReferenceCount()
		{
			return m_nRefCount;
		}
		inline bool IsLocked()
		{
			return (m_nRefCount > 0) ? true : false;
		}

		inline void SetLastAccess( time_t lastAccess )
		{
			m_lastAccess = lastAccess;
		}
		inline time_t GetLastAccess()
		{
			return m_lastAccess;
		}

		bool operator < (CHrBaseRes& container);
	protected:
		_PRIORITY_TYPE_ m_Priority = RES_LOW_PRIORITY;
		uint            m_nRefCount = 0;
		time_t          m_lastAccess = 0;
	};

}


#endif
