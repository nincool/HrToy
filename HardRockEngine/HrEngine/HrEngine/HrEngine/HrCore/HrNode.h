#ifndef _HR_NODE_H_
#define _HR_NODE_H_

#include "HrObject.h"

namespace Hr
{
	class CHrNode : public CHrObject, public CHrRef
	{
	public:
		CHrNode();
		~CHrNode();
	};

}


#endif
