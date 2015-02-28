#pragma once

namespace HrPool
{
	class CHrMemoryStack
	{
	public:
		CHrMemoryStack();
		~CHrMemoryStack();

	public:
		void*		Mallock( int nSize );
	};
}


