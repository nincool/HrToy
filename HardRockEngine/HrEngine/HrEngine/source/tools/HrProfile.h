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
		bool bValid;            //�����Ƿ���Ч
		char szName[256];       //�������� 
		float fStartTime;       //��ǰ������ʼʱ��
		float fLastTime;        //��������ʱ��

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
		bool bValid;             //�����Ƿ���Ч 
		char szName[256];        //��������
		float fAve;              //ÿ֡��ƽ��ʱ��(�ٷֱ�)
		float fMin;              //ÿ֡����Сʱ��(�ٷֱ�)
		float fMax;              //ÿ֡�����ʱ��(�ٷֱ�)
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

