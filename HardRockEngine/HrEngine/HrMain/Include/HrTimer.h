#ifndef _HR_TIMER_H_
#define _HR_TIMER_H_

#include "ITimer.h"

namespace Hr
{
	class HR_MAIN_API HrTimer : public ITimer
	{
	public:
		HrTimer();
		virtual ~HrTimer();

	public:
		virtual void ResetTimer() override;

		//The function Tick is called in the application message loop
		virtual void Tick() override;

		virtual float DeltaTime() override;

		virtual void PauseTimer() override;
		virtual void ContinueTimer() override;
	private:
		uint64 m_nFrameCount;
		//Last frame tic
		int64 m_nPrevTime;
		double m_dSecondsPerCount;
		double m_dDeltaTime;

		bool m_bPaused;
		//暂停发生时的时间
		int64 m_nPauseoccursTime;
		//暂停持续时间
		int64 m_nPauseTime;
	};
}

#endif

