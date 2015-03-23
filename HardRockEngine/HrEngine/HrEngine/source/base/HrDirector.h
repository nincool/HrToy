#ifndef _HR_DIRECTOR_H_
#define _HR_DIRECTOR_H_

#include "HrNode.h"

namespace Hr
{
	class CHrDirector : CHrNode
	{
	public:
		CHrDirector();
		~CHrDirector();

	public:
		virtual void MainLoop();


	};

}





#endif

