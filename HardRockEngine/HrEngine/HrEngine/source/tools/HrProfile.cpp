#include "stdafx.h"
#include "HrProfile.h"
#include <ctime>
#include <cassert>
#include "HrDebugNew.h"
#include <boost/format.hpp>

US_NS_HR;
using namespace std;

CHrListPool<SProfileSample> CHrProfile::m_s_listPool;
list<SProfileSample*> CHrProfile::m_s_lisProfileSamples;

float CHrProfile::m_fStartProfile;
float CHrProfile::m_fEndProfile;

uint CHrProfile::m_nOpenSamplesNum = 0;
uint CHrProfile::m_nEndSamplesNum = 0;

CHrProfile::CHrProfile()
{
}

CHrProfile::~CHrProfile()
{
}

void CHrProfile::InitProfileSamples()
{
	m_s_listPool.InitListPool( NUM_PROFILE_SAMPLES );
}

void CHrProfile::ReleaseProfile()
{
	m_s_listPool.Release();
}

void CHrProfile::Reset()
{
	m_fStartProfile = 0;
	m_fEndProfile = 0;
	m_nOpenSamplesNum = 0;
	m_nEndSamplesNum = 0;
}

SProfileSample* CHrProfile::FindChildSampleByName( SProfileSample* pSample, const char* name )
{
	if (strcmp( pSample->szName, name ) == 0)
	{
		if (pSample->bValid)
		{
			assert( !"Already has a profile sample" );
			return nullptr;
		}
		else
		{
			return pSample;
		}
	}
	else
	{
		if (pSample->pNext != nullptr)
		{
			FindChildSampleByName( pSample->pNext, name );
		}
	}

	return nullptr;
}

SProfileSample* CHrProfile::FindSample( const char* name )
{
	//这里感觉有性能影响
	for (auto& profileSample : m_s_lisProfileSamples)
	{
		if (profileSample->bValid)
		{
			if (strcmp( profileSample->szName, name ) == 0)
			{
				if (profileSample->bValid)
				{
					assert( !"Already has a profile sample" );
					return nullptr;
				}
				else
				{
					return profileSample;
				}
			}
			else if (profileSample->bValid)
			{
				if (profileSample->pNext != nullptr)
				{
					SProfileSample* pProfile = FindChildSampleByName( profileSample->pNext, name );
					if (pProfile != nullptr)
					{
						return pProfile;
					}
				}
			}
		}
	}
	return nullptr;
}

void CHrProfile::ProfileBegin( char* name )
{
	//检测是否存在同名正在运行样本
	SProfileSample* pProfileSample = FindSample( name );
	if (pProfileSample == nullptr)
	{
		pProfileSample = m_s_listPool.GetOneFree();
		pProfileSample->Reset();
	}
	else
	{
		//pProfileSample->
	}
	pProfileSample->bValid = true;
	STRCPY( pProfileSample->szName, sizeof( pProfileSample->szName ), name );
	pProfileSample->fStartTime = GetCurTimeFlag();

	//检测当前是否存在根样本 如果存在，那么进行链接
	SProfileSample* pParent = nullptr;
	if (m_s_lisProfileSamples.size() > 0)
	{
		pParent = m_s_lisProfileSamples.back();
		pParent->pNext = pProfileSample;
		pProfileSample->pPrevius = pParent;
	}
	
	m_s_lisProfileSamples.push_back( pProfileSample );
}

void CHrProfile::EndTailedSample(SProfileSample* pSample)
{
	if (pSample->pNext != nullptr)
	{
		EndTailedSample( pSample->pNext );
	}
	else
	{
		//设置关闭
		pSample->bValid = false;
		pSample->fLastTime = GetCurTimeFlag() - pSample->fStartTime;
	}
}

void CHrProfile::ProfileEnd()
{
	//默认关闭最后一个
	if (m_s_lisProfileSamples.size() <= 0)
	{
		assert( !"The samples is empty" );
	}
	SProfileSample* pProfileSample = m_s_lisProfileSamples.back();
	EndTailedSample( pProfileSample );
}

float CHrProfile::GetCurTimeFlag()
{
	return (float)(std::clock()) / CLOCKS_PER_SEC;
}

void CHrProfile::ProfileDumpOutputToBuffer()
{
	//检测是否存在没有关闭的Sample
	if (m_nOpenSamplesNum != m_nEndSamplesNum)
	{
		assert( !"ProfileBegin does not match ProfileEnd" );
	}

	//把所有收集到的数据打印出来
	/* 平均值 | 最小值 | 最大值 | 调用 | 剖析名 |*/
	boost::format fmt( "Ave | Max | Min | Call | Name\n" );
	
}

void CHrProfile::StoreProfileInHistory()
{

}

void CHrProfile::GetProfileFromHistory( char* name, float& fAve, float& fMin, float& fMax )
{
	
}

