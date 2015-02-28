#pragma once

namespace HrPool
{
	class CHrPoolManager
	{
	public:
		CHrPoolManager();
		~CHrPoolManager();

	public:

		void*		Malloc( int nSize, char* szInfo = NULL );
	};
}


