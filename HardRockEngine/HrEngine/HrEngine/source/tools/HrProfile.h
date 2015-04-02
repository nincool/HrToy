#ifndef _HR_PROFILE_H_
#define _HR_PROFILE_H_

#include "HrEngineCom.h"
#include <list>
#include "HrListPool.h"

namespace Hr
{
#define NUM_PROFILE_SAMPLES (50)

	struct SProfileSample
	{
		bool bValid;            //数据是否有效
		char szName[256];       //样本名称 
		float fStartTime;       //当前样本开始时间
		float fLastTime;        //样本持续时间

		SProfileSample* pPrevius;
		SProfileSample* pNext;
		SProfileSample()
		{
			Reset();
		}

		void Reset()
		{
			bValid = false;
			HR_ZEROMEM( szName, sizeof( szName ) );
			fStartTime = 0;

			pPrevius = NULL;
			pNext = NULL;
		}
	};


	struct SProfileSampleHistory
	{
		bool bValid;             //数据是否有效 
		char szName[256];        //样本名称
		float fAve;              //每帧的平均时间(百分比)
		float fMin;              //每帧的最小时间(百分比)
		float fMax;              //每帧的最大时间(百分比)
	};

	class CHrProfile
	{
	public:
		CHrProfile();
		~CHrProfile();

	public:
		static void Reset();

		static void ProfileBegin( char* name );

		static void ProfileEnd();

		static void ProfileDumpOutputToBuffer();

		static void StoreProfileInHistory();

		static void GetProfileFromHistory(char* name, float& fAve, float& fMin, float& fMax);

		static float GetCurTimeFlag();

	private:
		static SProfileSample* FindSample( const char* name );

		static SProfileSample* FindChildSampleByName( SProfileSample* pSample, const char* name );

		static void InitProfileSamples();
		static void ReleaseProfile();


		static void EndTailedSample( SProfileSample* pSample );
	public:
		static CHrListPool<SProfileSample> m_s_listPool;
		static std::list<SProfileSample*> m_s_lisProfileSamples;

		static float m_fStartProfile;
		static float m_fEndProfile;

	private:
		static uint m_nOpenSamplesNum;
		static uint m_nEndSamplesNum;
	};
}


#endif

