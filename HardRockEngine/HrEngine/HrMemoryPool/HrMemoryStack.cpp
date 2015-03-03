#include "stdafx.h"
#include "HrMemoryStack.h"
#include "HrLowDebug.h"

using namespace HrPool;
CHrMemoryStack::CHrMemoryStack(CHrLowDebug* pDebugLog)
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
		m_pDebugLog->Debug2File( "CHrMemoryStack::Mallock Error! Mallock MemorySize[%d]", nSize );

		return pRetMemory;
	}
	return pRetMemory;


}
