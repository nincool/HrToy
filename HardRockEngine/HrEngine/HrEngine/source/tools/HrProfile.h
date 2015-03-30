#ifndef _HR_PROFILE_H_
#define _HR_PROFILE_H_

#include "HrEngineCom.h"

namespace Hr
{
#define NUM_PROFILE_SAMPLES (50)

	struct SProfileSample
	{
		bool bValid;            //数据是否有效
		uint nProfileInstances; //PorfileBegin调用次数
		int  nOpenProfiles;     //没有相匹配ProfileEnd调用的ProfileBegin调用次数
		char szName[256];       //样本名称 
		float fStartTime;       //当前样本开始时间
		float fAccumulator;     //帧内所有样本总计
		float fChildrenSampleTime; //所有子样本耗时
		uint nNumParents;       //父样本数
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
		void ProfileBegin( char* name );

		static float GetCurTimeElapse();
	public:
		static SProfileSample m_samples[NUM_PROFILE_SAMPLES];
		static SProfileSampleHistory m_history[NUM_PROFILE_SAMPLES];
		

		static float m_fStartProfile;
		static float m_fEndProfile;
	};
}


#endif

