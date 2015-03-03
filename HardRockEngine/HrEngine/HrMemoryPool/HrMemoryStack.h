#pragma once

namespace HrPool
{
	class CHrLowDebug;
	class CHrMemoryStack
	{
	public:
		CHrMemoryStack(CHrLowDebug* pDebugLog);
		~CHrMemoryStack();

	public:
		void*				Mallock( int nSize );

	private:
		CHrLowDebug*		m_pDebugLog;
	};
}


