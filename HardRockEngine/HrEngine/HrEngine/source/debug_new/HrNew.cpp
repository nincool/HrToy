#include "stdafx.h"
#include "HrNew.h"

using namespace HrPool;

//��ʼ���ڴ��
std::shared_ptr<CHrPoolManager> CHrNew::m_s_pPoolManager( new CHrPoolManager(true) );

CHrNew::CHrNew()
{

}

CHrNew::~CHrNew()
{

}




