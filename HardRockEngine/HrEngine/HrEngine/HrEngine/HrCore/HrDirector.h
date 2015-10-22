#ifndef _HR_DIRECTOR_H_
#define _HR_DIRECTOR_H_

#include "HrNode.h"

namespace Hr
{
	class CHrDirector : public CHrNode
	{
	public:
		CHrDirector();
		~CHrDirector();

	public:
		virtual void MainLoop();


	};

}





#endif

