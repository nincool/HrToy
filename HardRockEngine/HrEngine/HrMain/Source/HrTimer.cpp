#include "HrTimer.h"

using namespace Hr;

HrTimer::HrTimer()
{
	m_nFrameCount = 0;
	m_nPrevTime = 0;
	m_dDeltaTime = 0;

	m_bPaused = false;
	m_nPauseoccursTime = 0;
	m_nPauseTime = 0;

	LARGE_INTEGER LICountsPerSecond;
	QueryPerformanceFrequency(&LICountsPerSecond);
	m_dSecondsPerCount = 1.0 / (double)(LICountsPerSecond.QuadPart);
}


HrTimer::~HrTimer()
{
}

void HrTimer::ResetTimer()
{
	m_nFrameCount = 0;
	m_bPaused = false;
	m_nPauseoccursTime = 0;
	m_nPauseTime = 0;

	LARGE_INTEGER LICurrentTime;
	QueryPerformanceCounter(&LICurrentTime);
	m_nPrevTime = LICurrentTime.QuadPart;

}

void HrTimer::Tick()
{
	int64 nCurrentTime = 0;
	LARGE_INTEGER LICurrentTime;
	QueryPerformanceCounter(&LICurrentTime);
	nCurrentTime = LICurrentTime.QuadPart;

	m_dDeltaTime = (nCurrentTime - m_nPrevTime) * m_dSecondsPerCount;
	// Force nonnegative. The DXSDK's CDXUTTimer mentions that if the
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (m_dDeltaTime < 0.0)
	{
		m_dDeltaTime = 0.0;
	}

	m_nPrevTime = nCurrentTime;
}

float HrTimer::DeltaTime()
{
	return (float)m_dDeltaTime;
}

void HrTimer::PauseTimer()
{
	if (m_bPaused)
	{
		return;
	}
	int64 nCurrentTime = 0;
	LARGE_INTEGER LICurrentTime;
	QueryPerformanceCounter(&LICurrentTime);
	nCurrentTime = LICurrentTime.QuadPart;

	m_nPauseoccursTime = nCurrentTime;
	m_bPaused = true;
}

void HrTimer::ContinueTimer()
{
	if (!m_bPaused)
	{
		return;
	}
	int64 nCurrentTime = 0;
	LARGE_INTEGER LICurrentTime;
	QueryPerformanceCounter(&LICurrentTime);
	nCurrentTime = LICurrentTime.QuadPart;

	m_nPauseTime += (nCurrentTime - m_nPauseoccursTime);
	m_nPauseoccursTime = 0;
	m_nPrevTime = nCurrentTime;
	m_bPaused = false;
}
