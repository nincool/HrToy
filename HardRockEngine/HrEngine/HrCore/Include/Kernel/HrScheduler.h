#ifndef _HR_SCHEDULER_H_
#define _HR_SCHEDULER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include <limits>

namespace Hr
{
	typedef std::function<void(float)> HrSchedulerFunc;

	class HrSchedulerTimer
	{
	public:
		HrSchedulerTimer(HrSchedulerPtr pScheduler);
		~HrSchedulerTimer();

		inline float GetInterval() const { return m_fInterval; }

		inline void SetInterval(float fInterval) { m_fInterval = fInterval; }

		void InitTimer(HrSchedulerFunc callBack, size_t nTargetHashKey, size_t nHashKey, float fInterval, uint32 nTriggerTimes, float fDelay);

		void Trigger(float fDelta);

		void Cancel();

		void Update(float fDelta);

		size_t GetTargetHashKey() { return m_nTargetHashKey; }
		size_t GetHashKey() { return m_nHashKey; }

	protected:
		HrWeakSchedulerPtr m_pScheduler;
		float m_fElapsed;
		bool m_bRunForever;
		bool m_bUseDelay;
		uint32 m_nTimesExecuted;
		uint32 m_nTriggerTimes; 
		float m_fDelay;
		float m_fInterval;

		HrSchedulerFunc m_func;
		size_t m_nTargetHashKey;
		size_t m_nHashKey;

	};

	class HR_CORE_API HrScheduler : public std::enable_shared_from_this<HrScheduler>
	{
	public:
		HrScheduler();
		virtual ~HrScheduler();

		void Update(float fDetal);

		/////////////////////////////////////////////
		//schedule
		/////////////////////////////////////////////

		void Schedule(HrSchedulerFunc callBack, void* pTarget, const std::string& strKey, float fInterval, uint32 nRepeat, float fDelay);

		void UnShcedule(void* pTarget, const std::string& strKey);

		void UnSchedule(size_t nTargetHashKeyID, size_t nHashID);
	protected:
		HrSchedulerTimer* GetFreeSchedulerTimer();
		void RecycleSchedulerTimer(HrSchedulerTimer* pSchedulerTimer);
		void ReleaseSchedulerTimers();
	protected:
		std::unordered_map<size_t, std::list<HrSchedulerTimer*>> m_mapSchedulerTimer;
		std::vector<std::pair<size_t, size_t>> m_vecReadyTimersInfoReadyErase;

		std::list<HrSchedulerTimer*> m_lisSchedulerTimersPool;
		
	};
}

#endif



