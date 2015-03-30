#include "stdafx.h"
#include "HrBaseRes.h"

using namespace Hr;
CHrBaseRes::CHrBaseRes()
{
}


CHrBaseRes::~CHrBaseRes()
{
}

bool CHrBaseRes::operator<(CHrBaseRes& container)
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
