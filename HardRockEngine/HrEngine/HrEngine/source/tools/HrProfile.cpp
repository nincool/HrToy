#include "stdafx.h"
#include "HrProfile.h"
#include <ctime>
#include <cassert>

using namespace Hr;

static SProfileSample m_samples[NUM_PROFILE_SAMPLES];
static SProfileSampleHistory m_history[NUM_PROFILE_SAMPLES];

static float m_fStartProfile;
static float m_fEndProfile;

SProfileSample CHrProfile::m_samples[NUM_PROFILE_SAMPLES];
SProfileSampleHistory CHrProfile::m_history[NUM_PROFILE_SAMPLES];

float CHrProfile::m_fStartProfile;
float CHrProfile::m_fEndProfile;

CHrProfile::CHrProfile()
{
}


CHrProfile::~CHrProfile()
{
}

void CHrProfile::ProfileBegin( char* name )
{
	uint i = 0;

	while (i < NUM_PROFILE_SAMPLES && m_samples[i].bValid)
	{
		if (strcmp( m_samples[i].szName, name ) == 0)
		{
			//�ҵ�һ��ͬ������
			++m_samples[i].nOpenProfiles;
			++m_samples[i].nProfileInstances;
			m_samples[i].fStartTime = GetCurTimeFlag();
			//ÿ�ε����ֵΪ1
			assert( m_samples[i].nOpenProfiles == 1 );

			return;
		}
		++i;
	}

	if (i >= NUM_PROFILE_SAMPLES)
	{
		assert( !"Exceeded max Available Profile Samples" );
		return;
	}
	
	strcpy(m_samples[i].szName, name);
	m_samples[i].bValid = true;
	m_samples[i].nProfileInstances = 1;
	m_samples[i].fAccumulator = 0.0f;
	m_samples[i].fStartTime = GetCurTimeFlag();
	m_samples[i].fChildrenSampleTime = 0.0f;
}

void CHrProfile::ProfileEnd( char* name )
{
	uint i = 0;
	uint nNumParents = 0;

	while (i < NUM_PROFILE_SAMPLES && m_samples[i].bValid)
	{
		if (strcmp( m_samples[i].szName, name ) == 0)
		{
			//�ҵ�һ������
			uint nInner = 0;
			int nParent = -1;
			float fEndTime = GetCurTimeFlag();
			--m_samples[i].nOpenProfiles;

			//ͳ�����и��ڵ㲢�ҵ�ֱ�Ӹ��ڵ�
			while (m_samples[nInner].bValid)
			{
				if (m_samples[nInner].nOpenProfiles > 0)
				{
					//�ҵ�һ�����ڵ�(�κο��ŵĽڵ㶼�Ǹ��ڵ�)
					++nNumParents;
					if (nParent < 0)
					{
						//�滻��Ч���ڵ�(����)
						nParent = nInner;
					}
					else if (m_samples[nInner].fStartTime >= m_samples[nParent].fStartTime)
					{
						nParent = nInner;
					}
				}

				++nInner;
			}

			//��¼�������ڵ㵱ǰ����
			m_samples[i].nNumParents = nNumParents;

			if (nParent >= 0)
			{
				//��¼ʱ�䵽FChildrenSampleTime(�ۼ�)
				m_samples[nParent].fChildrenSampleTime += fEndTime - m_samples[i].fStartTime;
			}

			//�����ۻ�����ʱ��
			m_samples[i].fAccumulator += fEndTime - m_samples[i].fStartTime;
			
			return;
		}
		++i;
	}
}

float CHrProfile::GetCurTimeFlag()
{
	return (float)(std::clock()) / CLOCKS_PER_SEC;
}

void CHrProfile::ProfileDumpOutputToBuffer()
{


	m_fEndProfile = GetCurTimeFlag();
	//ClearTextBuffer();

	//PutTexBuffer(" Ave : Min : Max : # Profile Name \n");
	//PutTexBuffer( "-----------------------------------------\n" );
	uint i = 0;
	while (i < NUM_PROFILE_SAMPLES && m_samples[i].bValid)
	{
		uint nIndent = 0;
		float fSampleTime, fPercentTime, fAveTime, fMinTime, fMaxTime;
		char szLine[256], szName[256], szIndentedName[256];
		char fAve[16], fMin[16], fMax[16], fNum[16];

		if (m_samples[i].nOpenProfiles < 0)
		{
			assert( !"ProfileEnd() called without a ProfileBegin()" );
		}
		else if (m_samples[i].nOpenProfiles > 0)
		{
			assert( !"ProfileBegin() called without a ProfileEnd()" );
		}

		fSampleTime = m_samples[i].fAccumulator - m_samples[i].fChildrenSampleTime;
		fPercentTime = (fSampleTime / (m_fEndProfile - m_fStartProfile)) * 100.0f;

		fAveTime = fMinTime = fMaxTime = fPercentTime;

		//����ʷ��¼�������µĲ���ֵ������ȡƽ������С�����ֵ
		//StoreProfileInHistory( m_samples[i].szName, fPercentTime );
		//GetProfileFromHistory( m_samples[i].szName, &fAveTime, &fMinTime, &fMaxTime );

		//��ʽ�����ݲ������

	
		
	}
	//Ϊ��һ֡������������
	for (uint n = 0; n < NUM_PROFILE_SAMPLES; ++n)
	{
		m_samples[n].bValid = false;
	}

	m_fStartProfile = GetCurTimeFlag();
}

void CHrProfile::StoreProfileInHistory()
{
	uint i = 0;
	float fOldRatio;
	//float fNewRatio = 0.8f * GetElapseTime();
}

void CHrProfile::GetProfileFromHistory( char* name, float& fAve, float& fMin, float& fMax )
{
	
}
