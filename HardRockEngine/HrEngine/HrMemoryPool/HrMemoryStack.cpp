#include "stdafx.h"
#include "HrMemoryStack.h"

using namespace HrPool;
CHrMemoryStack::CHrMemoryStack()
{
}


CHrMemoryStack::~CHrMemoryStack()
{
}

void* CHrMemoryStack::Mallock( int nSize )
{
	void* pRetMemory = nullptr;
	if (0 >= nSize)
	{
		//m_pDebug->Debug2File( "CHrMemoryStack::Malloc():ERROR! iSize=%d\n", iSize );

		//return pRet;
	}
	return pRetMemory;
}
