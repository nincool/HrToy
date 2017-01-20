#include "Kernel/HrScheduler.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;


/////////////////////////////////////////////////////
//HrSchedulerTimer
/////////////////////////////////////////////////////

HrSchedulerTimer::HrSchedulerTimer(HrSchedulerPtr pScheduler):m_pScheduler(pScheduler)
{
	m_fElapsed = 0;
	m_bRunForever = false;
	m_bUseDelay = false;
	m_nTimesExecuted = 0;
	m_nTriggerTimes = 0;
	m_fDelay = 0;
	m_fInterval = 0;

	m_nTargetHashKey = 0;
	m_nHashKey = 0;
}

HrSchedulerTimer::~HrSchedulerTimer()
{
}

void HrSchedulerTimer::InitTimer(HrSchedulerFunc callBack, size_t nTargetHashKey, size_t nHashKey, float fInterval, uint32 nTriggerTimes, float fDelay)
{
	m_fElapsed = -1;
	m_fInterval = fInterval;
	m_fDelay = fDelay;
	m_bUseDelay = (m_fDelay > 0.0f) ? true : false;
	m_nTriggerTimes = nTriggerTimes;
	m_bRunForever = (nTriggerTimes == 0) ? true : false;
	m_nTimesExecuted = 0;

	m_func = callBack;
	m_nTargetHashKey = nTargetHashKey;
	m_nHashKey = nHashKey;
}

void HrSchedulerTimer::Update(float fDelta)
{
	//give up the first update
	if (m_fElapsed == -1)
	{
		m_fElapsed = 0;
		m_nTimesExecuted = 0;
		return;
	}
	
	//accumulate elapsed time
	m_fElapsed += fDelta;

	// deal with delay
	if (m_bUseDelay)
	{
		if (m_fElapsed < m_fDelay)
		{
			return;
		}
		Trigger(m_fElapsed);
		m_fElapsed = m_fElapsed - m_fDelay;
		++m_nTimesExecuted;
		m_bUseDelay = false;

		if (!m_bRunForever && m_nTimesExecuted >= m_nTriggerTimes)
		{
			Cancel();

			return;
		}
	}

	// if m_bInterval == 0, should trigger once every frame
	float fInterval = (m_fInterval > 0) ? m_fInterval : m_fElapsed;
	while (m_fElapsed >= fInterval)
	{
		Trigger(fInterval);
		m_fElapsed -= fInterval;
		++m_nTimesExecuted;

		if (!m_bRunForever && m_nTimesExecuted >= m_nTriggerTimes)
		{
			Cancel();

			break;
		}
		
		if (m_fElapsed <= 0.0f)
		{
			break;
		}
	}
}

void HrSchedulerTimer::Trigger(float fDelta)
{
	if (m_func)
	{
		m_func(fDelta);
	}
}

void HrSchedulerTimer::Cancel()
{
	if (!m_pScheduler.expired())
	{
		auto& pScheduler = m_pScheduler.lock();
		pScheduler->UnSchedule(m_nTargetHashKey, m_nHashKey);
	}
}

/////////////////////////////////////////////////////
//HrScheduler
/////////////////////////////////////////////////////
HrScheduler::HrScheduler()
{

}

HrScheduler::~HrScheduler()
{
	ReleaseSchedulerTimers();
}

void HrScheduler::Update(float fDetal)
{
	//因为有可能在Update的时候就会销毁，所以应该把准备销毁的缓存起来最后统一销毁
	if (!m_mapSchedulerTimer.empty())
	{
		for (auto itemTargetTimers : m_mapSchedulerTimer)
		{
			for (auto itemTimer : itemTargetTimers.second)
			{
				itemTimer->Update(fDetal);
			}
		}
	}

	for (auto& itemReadyErase : m_vecReadyTimersInfoReadyErase)
	{
		auto itemTargetTimers = m_mapSchedulerTimer.find(itemReadyErase.first);
		if (itemTargetTimers != m_mapSchedulerTimer.end())
		{
			for (auto itemTimer = itemTargetTimers->second.begin(); itemTimer != itemTargetTimers->second.end(); ++itemTimer)
			{
				if ((*itemTimer)->GetHashKey() == itemReadyErase.second)
				{
					itemTargetTimers->second.erase(itemTimer);
					if (itemTargetTimers->second.empty())
					{
						m_mapSchedulerTimer.erase(itemTargetTimers);
					}
					break;
				}
			}
		}
	}
	m_vecReadyTimersInfoReadyErase.clear();
}

void HrScheduler::Schedule(HrSchedulerFunc callBack, void* pTarget, const std::string& strKey, float fInterval, uint32 nRepeat, float fDelay)
{
	HRASSERT(pTarget, "Argument pTarget must be non-nullptr");
	HRASSERT(!strKey.empty(), "strKey should not be empty");

	size_t nTargetHashKey = reinterpret_cast<size_t>(pTarget);
	size_t nTimerHashKey = HrHashValue(strKey);
	auto itemTargetTimers = m_mapSchedulerTimer.find(nTargetHashKey);
	if (itemTargetTimers != m_mapSchedulerTimer.end())
	{
#if HR_DEBUG >= 1
		for (auto& itemTimer : itemTargetTimers->second)
		{
			if (itemTimer->GetHashKey() == nTimerHashKey)
			{
				HRASSERT(nullptr, "Already Scheduled!");
				return;
			}
		}
#endif

		HrSchedulerTimer* pSchedulerTimer = GetFreeSchedulerTimer();
		itemTargetTimers->second.push_back(pSchedulerTimer);
		pSchedulerTimer->InitTimer(callBack, nTargetHashKey, nTimerHashKey, fInterval, nRepeat, fDelay);
	}
	else
	{
		std::list<HrSchedulerTimer*> lisTargetSchedulerTimers;
		HrSchedulerTimer* pSchedulerTimer = GetFreeSchedulerTimer();
		lisTargetSchedulerTimers.push_back(pSchedulerTimer);
		m_mapSchedulerTimer.emplace(nTargetHashKey, lisTargetSchedulerTimers);
		//m_mapSchedulerTimer[nTargetHashKey] = lisTargetSchedulerTimers;

		pSchedulerTimer->InitTimer(callBack, nTargetHashKey, nTimerHashKey, fInterval, nRepeat, fDelay);
	}
}

void HrScheduler::UnShcedule(void* pTarget, const std::string& strKey)
{

}

void HrScheduler::UnSchedule(size_t nTargetHashKeyID, size_t nHashID)
{
	m_vecReadyTimersInfoReadyErase.push_back(std::pair<size_t, size_t>(nTargetHashKeyID, nHashID));
}

HrSchedulerTimer* HrScheduler::GetFreeSchedulerTimer()
{
	if (!m_lisSchedulerTimersPool.empty())
	{
		HrSchedulerTimer* pSchedulerTimer = m_lisSchedulerTimersPool.front();
		m_lisSchedulerTimersPool.pop_front();

		return pSchedulerTimer;
	}
	else
	{
		HrSchedulerTimer* pSchedulerTimer = HR_NEW HrSchedulerTimer(shared_from_this());

		return pSchedulerTimer;
	}
}

void HrScheduler::RecycleSchedulerTimer(HrSchedulerTimer* pSchedulerTimer)
{
	m_lisSchedulerTimersPool.push_back(pSchedulerTimer);
}

void HrScheduler::ReleaseSchedulerTimers()
{
	for (auto& itemTargetTimes : m_mapSchedulerTimer)
	{
		for (auto& itemTimer : itemTargetTimes.second)
		{
			RecycleSchedulerTimer(itemTimer);
		}
	}
	m_mapSchedulerTimer.clear();
	
	for (auto& itemTimer : m_lisSchedulerTimersPool)
	{
		SAFE_DELETE(itemTimer);
	}
	m_lisSchedulerTimersPool.clear();
}

