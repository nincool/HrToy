#ifndef _HR_PROFILE_H_
#define _HR_PROFILE_H_

#include "HrEngineCom.h"

namespace Hr
{
#define NUM_PROFILE_SAMPLES (50)

	struct SProfileSample
	{
		bool bValid;            //�����Ƿ���Ч
		uint nProfileInstances; //PorfileBegin���ô���
		int  nOpenProfiles;     //û����ƥ��ProfileEnd���õ�ProfileBegin���ô���
		char szName[256];       //�������� 
		float fStartTime;       //��ǰ������ʼʱ��
		float fAccumulator;     //֡�����������ܼ�
		float fChildrenSampleTime; //������������ʱ
		uint nNumParents;       //��������
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

