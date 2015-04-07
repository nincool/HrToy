#ifndef _HR_PROFILE_H_
#define _HR_PROFILE_H_

#include "HrEngineCom.h"
#include "HrListPool.h"
#include <list>


namespace Hr
{
#define NUM_PROFILE_SAMPLES (50)

	struct SProfileSample
	{
		bool bValid;            //数据是否有效
		char szName[256];       //样本名称 
		int nOpenInstance;      //样本被打开的次数
		float fStartTime;       //当前样本开始时间
		float fLastTime;        //样本持续时间


		SProfileSample* pPrevius;
		SProfileSample* pNext;

		SProfileSample* pParent;
		SProfileSample* pChild;

		SProfileSample()
		{
			Reset();
		}

		void Reset()
		{
			bValid = false;
			HR_ZEROMEM( szName, sizeof( szName ) );
			fStartTime = 0;
			fLastTime = 0;
			nOpenInstance = 0;

			pPrevius = nullptr;
			pParent = nullptr;
			pChild = nullptr;
			pNext = nullptr;
		}
	};

	struct SProfileSampleHistory
	{
		char szName[256];        //样本名称
		float fAve;              //每帧的平均时间(百分比)
		float fMin;              //每帧的最小时间(百分比)
		float fMax;              //每帧的最大时间(百分比)
		uint nHistoryOpenNum;    //历史记录次数
		float fTotalLastTime;

		SProfileSampleHistory()
		{
			Reset();
		}
		void Reset()
		{
			memset( szName, 0, sizeof( szName ) );
			fAve = 0;
			fMin = 999;
			fMax = 0;
			nHistoryOpenNum = 0;
			fTotalLastTime = 0;
		}
	};

	class CHrProfile
	{
	public:
		CHrProfile();
		~CHrProfile();

	public:
		/**
		 *	@Brief: 初始化性能分析 [4/3/2015 By Hr]
		*/
		static void InitProfileSamples();
		static void ReleaseProfile();

		static void Reset();

		/**
		 *	@Brief: 开启一个性能分析样本 [4/3/2015 By Hr]
		*/
		static void ProfileBegin( char* name );

		static void ProfileEnd();

		/**
		 *	@Brief: 定向输出 [4/3/2015 By Hr]
		*/
		static void ProfileDumpOutputToBuffer();

		static void StoreProfileInHistory();

		static void GetProfileFromHistory(char* name, float& fAve, float& fMin, float& fMax);

		static float GetCurTimeFlag();

	private:
		static SProfileSample* FindSample( SProfileSample* pProfileSample, const char* name );

		static bool EndTailedSample( SProfileSample* pSample );

		static void DumpOneSampleToBuffer( SProfileSample* pProfileSample );

		static void ClearSample(SProfileSample* pSample);
	public:
		static CHrListPool<SProfileSample> m_s_listPool;

		static std::list<SProfileSampleHistory*> m_s_lisProfileSampleHistory;

		static SProfileSample* m_s_pRootProfileSample;
		static SProfileSample* m_s_pTailedProfileSample;

		static float m_fStartProfile;
		static float m_fEndProfile;

	private:
		static uint m_nOpenSamplesNum;
		static uint m_nEndSamplesNum;
	};
}


#endif

