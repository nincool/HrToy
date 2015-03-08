#include "stdafx.h"
#include "HrNew.h"

using namespace HrPool;

//³õÊ¼»¯ÄÚ´æ³Ø
std::shared_ptr<CHrPoolManager> CHrNew::m_s_pPoolManager( new CHrPoolManager(true) );

CHrNew::CHrNew()
{

}

CHrNew::~CHrNew()
{

}




