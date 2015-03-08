#ifndef _HR_MUTEXLOCK_H_
#define _HR_MUTEXLOCK_H_

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

//采用临界区
#ifdef WIN32

#define MUTEX					CRITICAL_SECTION
#define MUTEXINIT(m)			InitializeCriticalSection(m)
#define MUTEXLOCK(m)			EnterCriticalSection(m)
#define MUTEXUNLOCK(m)			LeaveCriticalSection(m)
#define MUTEXDESTROY(m)			DeleteCriticalSection(m)

#else //not win32

#define MUTEX					pthread_mutex_t
#define MUTEXINIT(m)			pthread_mutex_init(m, NULL)
#define MUTEXLOCK(m)			pthread_mutex_lock(m)
#define MUTEXUNLOCK(m)			pthread_mutex_unlock(m)
#define MUTEXDESTROY(m)			pthread_mutex_destroy(m)

#endif

class CHrMutexLock
{
public:
	CHrMutexLock()
	{
		MUTEXINIT( &m_Lock );
	}

	~CHrMutexLock()
	{
		MUTEXDESTROY( &m_Lock );
	}

public:
	void	Lock()
	{
		MUTEXLOCK( &m_Lock );
	}
	void	UnLock()
	{
		MUTEXUNLOCK( &m_Lock );
	}

private:
	MUTEX	m_Lock;
};

#endif

