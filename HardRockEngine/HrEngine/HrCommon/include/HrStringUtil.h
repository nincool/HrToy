#ifndef _HR_STRINGUTIL_H_
#define _HR_STRINGUTIL_H_

#include <string>

namespace Hr
{
	class HrStringUtil
	{
	public:
		static void Trim(std::string& str, bool left = true, bool right = true)
		{
			static const std::string delims = " \t\r";
			if (right)
				str.erase(str.find_last_not_of(delims) + 1); // trim right
			if (left)
				str.erase(0, str.find_first_not_of(delims)); // trim left
		}
	};
}


#endif

