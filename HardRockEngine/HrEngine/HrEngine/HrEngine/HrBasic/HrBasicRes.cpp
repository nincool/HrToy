#include "HrBasicRes.h"

using namespace Hr;
CHrBasicRes::CHrBasicRes()
{
}


CHrBasicRes::~CHrBasicRes()
{
}

bool CHrBasicRes::operator<(CHrBasicRes& container)
{
	if (GetPriority() < container.GetPriority())
	{
		return true;
	}
	else if (GetPriority() > container.GetPriority())
	{
		return false;
	}
	else
	{
		if (GetSize() < container.GetSize())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
