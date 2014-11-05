#include "HrMutexLock.h"

CHrMutexLock::CHrMutexLock(void)
{
	MUTEXINIT(&m_Lock);
}

CHrMutexLock::~CHrMutexLock(void)
{
	MUTEXDESTROY(&m_Lock);
}

void CHrMutexLock::Lock()
{
	MUTEXLOCK(&m_Lock);
}

void CHrMutexLock::UnLock()
{
	MUTEXUNLOCK(&m_Lock);
}
