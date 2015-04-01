#include "stdafx.h"
#include "HrProfile.h"
#include <ctime>

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
			//找到一个样本
			++m_samples[i].nOpenProfiles;
			++m_samples[i].nProfileInstances;
			m_samples[i].fStartTime = GetCurTimeElapse();
		}
	}
}

float CHrProfile::GetCurTimeElapse()
{
	return (float)(std::clock()) / CLOCKS_PER_SEC;
}
