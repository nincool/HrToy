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
		bool bValid;            //�����Ƿ���Ч
		char szName[256];       //�������� 
		int nOpenInstance;      //�������򿪵Ĵ���
		float fStartTime;       //��ǰ������ʼʱ��
		float fLastTime;        //��������ʱ��


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
		char szName[256];        //��������
		float fAve;              //ÿ֡��ƽ��ʱ��(�ٷֱ�)
		float fMin;              //ÿ֡����Сʱ��(�ٷֱ�)
		float fMax;              //ÿ֡�����ʱ��(�ٷֱ�)
		uint nHistoryOpenNum;    //��ʷ��¼����
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
		 *	@Brief: ��ʼ�����ܷ��� [4/3/2015 By Hr]
		*/
		static void InitProfileSamples();
		static void ReleaseProfile();

		static void Reset();

		/**
		 *	@Brief: ����һ�����ܷ������� [4/3/2015 By Hr]
		*/
		static void ProfileBegin( char* name );

		static void ProfileEnd();

		/**
		 *	@Brief: ������� [4/3/2015 By Hr]
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

