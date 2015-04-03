#include "stdafx.h"
#include "HrProfile.h"
#include <ctime>
#include <cassert>
#include "HrDebugNew.h"
#include <boost/format.hpp>
#include <iostream>

US_NS_HR;
using namespace std;

CHrListPool<SProfileSample> CHrProfile::m_s_listPool;
list<SProfileSampleHistory*> CHrProfile::m_s_lisProfileSampleHistory;
SProfileSample* CHrProfile::m_s_pRootProfileSample = nullptr;
SProfileSample* CHrProfile::m_s_pTailedProfileSample = nullptr;

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
	for (auto& historyProfile : m_s_lisProfileSampleHistory)
	{
		HR_DELETE( historyProfile );
	}
	m_s_lisProfileSampleHistory.clear();

	m_s_listPool.Release();
}

void CHrProfile::Reset()
{
	m_fStartProfile = 0;
	m_fEndProfile = 0;
	m_nOpenSamplesNum = 0;
	m_nEndSamplesNum = 0;
	m_s_pRootProfileSample = nullptr;
	m_s_pTailedProfileSample = nullptr;
}

SProfileSample* CHrProfile::FindSample( SProfileSample* pProfileSample, const char* name )
{
	if (pProfileSample == nullptr)
	{
		return nullptr;
	}
	//遍历查找，不能图省事
	//1.校验自身 
	if (strcmp( pProfileSample->szName, name ) == 0)
	{
		if (pProfileSample->bValid)
		{
			assert( !"Already has the sample!" );
			return nullptr;
		}
		else
		{
			return pProfileSample;
		}
	}
	
	if (pProfileSample->bValid)
	{
		//2.判断孩子节点
		if (pProfileSample->pChild != nullptr)
		{
			SProfileSample* pPropfileSample = FindSample( pProfileSample->pChild, name );
			if (pPropfileSample != nullptr)
			{
				return pPropfileSample;
			}
		}


		//3.判断下一节点(小的根)
		if (pProfileSample->pNext != nullptr)
		{
			SProfileSample* pPropfileSample = FindSample( pProfileSample->pNext, name );;
			if (pPropfileSample != nullptr)
			{
				return pPropfileSample;
			}
		}
	}

	return nullptr;
}

void CHrProfile::ProfileBegin( char* name )
{
	//检测是否存在同名正在运行样本
	SProfileSample* pProfileSample = FindSample(m_s_pRootProfileSample, name );
	if (pProfileSample == nullptr)
	{
		pProfileSample = m_s_listPool.GetOneFree();
		if (m_s_pRootProfileSample == nullptr)
		{
			m_s_pRootProfileSample = pProfileSample;
		}
	}
	pProfileSample->Reset();

	pProfileSample->bValid = true;
	++pProfileSample->nOpenInstance;
	STRCPY( pProfileSample->szName, sizeof( pProfileSample->szName ), name );
	pProfileSample->fStartTime = GetCurTimeFlag();

	//1.判断尾节点是否为子根节点 ->Parent是否为NULL
	if (m_s_pTailedProfileSample != nullptr)
	{
		if (m_s_pTailedProfileSample->pParent == nullptr)
		{
			if (m_s_pTailedProfileSample->bValid)
			{
				//新节点作为子节点链接到这个根节点中
				m_s_pTailedProfileSample->pChild = pProfileSample;
				pProfileSample->pParent = m_s_pTailedProfileSample;
				m_s_pTailedProfileSample = pProfileSample;
			}
			else
			{
				//新节点作为根节点链接到这个根链表
				m_s_pTailedProfileSample->pNext = pProfileSample;
				pProfileSample->pPrevius = m_s_pTailedProfileSample;
				m_s_pTailedProfileSample = pProfileSample;
			}
		}
		else
		{
			//不为根节点，那么直接链接进去
			m_s_pTailedProfileSample->pChild = pProfileSample;
			pProfileSample->pParent = m_s_pTailedProfileSample;
			m_s_pTailedProfileSample = pProfileSample;
		}
	}
	else
	{
		m_s_pTailedProfileSample = pProfileSample;
	}
}

bool CHrProfile::EndTailedSample(SProfileSample* pSample)
{
	if (pSample->bValid)
	{
		pSample->bValid = false;
		pSample->fLastTime += GetCurTimeFlag() - pSample->fStartTime;

		//查找对应的历史记录样本
		SProfileSampleHistory* pHistorySample = nullptr;
		for (auto& historySample : m_s_lisProfileSampleHistory)
		{
			if (strcmp( historySample->szName, pSample->szName ) == 0)
			{
				pHistorySample = historySample;
				break;
			}
		}
		if (pHistorySample == nullptr)
		{
			pHistorySample = HR_NEW( SProfileSampleHistory );
			m_s_lisProfileSampleHistory.push_back( pHistorySample );
			STRCPY( pHistorySample->szName, sizeof(pHistorySample->szName),  pSample->szName );
		}
		++pHistorySample->nHistoryOpenNum;
		pHistorySample->fTotalLastTime += pSample->fLastTime;
		pHistorySample->fAve = pHistorySample->fTotalLastTime / pHistorySample->nHistoryOpenNum;
		pHistorySample->fMax = pSample->fLastTime > pHistorySample->fMax ? pSample->fLastTime : pHistorySample->fMax;
		pHistorySample->fMin = pSample->fLastTime < pHistorySample->fMin ? pSample->fLastTime : pHistorySample->fMin;

		return true;
	}
	assert( !"Profile End Error!" );
	return false;
}

void CHrProfile::ProfileEnd()
{
	if (m_s_pTailedProfileSample != nullptr)
	{
		SProfileSample* pParent = m_s_pTailedProfileSample->pParent;
		if (pParent != nullptr)
		{
			EndTailedSample( m_s_pTailedProfileSample );
			m_s_pTailedProfileSample = pParent;
		}
		else
		{
			//自身就是一个根结点，那么去掉根结点链表的自身
			SProfileSample* pPrevios = m_s_pTailedProfileSample->pPrevius;
			SProfileSample* pNext = m_s_pTailedProfileSample->pNext;

			EndTailedSample( m_s_pTailedProfileSample );
		}
	}
	else
	{
		assert( !"Profile End Error!" );
	}
}

float CHrProfile::GetCurTimeFlag()
{
	return (float)(std::clock()) / CLOCKS_PER_SEC;
}

void CHrProfile::DumpOneSampleToBuffer(SProfileSample* pProfileSample)
{
	if (pProfileSample == nullptr)
	{
		return;
	}

	SProfileSampleHistory* pHistoryProfile = nullptr;
	for (auto& historyProfile : m_s_lisProfileSampleHistory)
	{
		if (strcmp( historyProfile->szName, pProfileSample->szName ) == 0)
		{
			pHistoryProfile = historyProfile;
			break;
		}
	}
	if (pHistoryProfile == nullptr)
	{
		assert( !"the profile error!" );
	}

	//1.输出自身
	boost::format fmt( " %-5.3f   %-5.3f   %-5.3f  %-5.3f  %-5.3f    %d    %s" );
	float fLastTime = pProfileSample->fLastTime;
	float fAveTime = pProfileSample->fLastTime / pProfileSample->nOpenInstance;
	float fTotalAve = pHistoryProfile->fAve;
	float fMaxTime = pHistoryProfile->fMax;
	float fMinTime = pHistoryProfile->fMin;
	fmt % fLastTime % fAveTime % fTotalAve % fMaxTime % fMinTime % pProfileSample->nOpenInstance % pProfileSample->szName;
	cout << fmt.str() << endl;

	if (pProfileSample->pChild != nullptr)
	{
		DumpOneSampleToBuffer( pProfileSample->pChild );
	}

	if (pProfileSample->pNext != nullptr)
	{
		DumpOneSampleToBuffer( pProfileSample->pNext );
	}
}

void CHrProfile::ProfileDumpOutputToBuffer()
{
	system( "cls" );
	
	//检测是否存在没有关闭的Sample
	if (m_nOpenSamplesNum != m_nEndSamplesNum)
	{
		assert( !"ProfileBegin does not match ProfileEnd" );
	}

	cout << "  Cur  |  Ave  |  TotalAve  |  Max  |  Min  |  Call  |  Name  " << endl;

	DumpOneSampleToBuffer( m_s_pRootProfileSample );

	//清除Profile链表
	ClearSample( m_s_pRootProfileSample );

	int nUserNum = m_s_listPool.GetUsedSize();
}

void CHrProfile::ClearSample( SProfileSample* pSample )
{
	if (pSample == nullptr)
	{
		return;
	}

	if (pSample->pNext != nullptr)
	{
		ClearSample( pSample->pNext );
	}
	
	if (pSample->pChild != nullptr)
	{
		ClearSample( pSample->pChild );
	}
	
	m_s_listPool.RecycleOne( pSample );
	if (pSample == m_s_pRootProfileSample)
	{
		m_s_pRootProfileSample = nullptr;
		m_s_pTailedProfileSample = nullptr;
	}
	return;
}

void CHrProfile::StoreProfileInHistory()
{

}

void CHrProfile::GetProfileFromHistory( char* name, float& fAve, float& fMin, float& fMax )
{
	
}

