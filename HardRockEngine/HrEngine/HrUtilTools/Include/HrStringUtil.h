#ifndef _HR_STRINGUTIL_H_
#define _HR_STRINGUTIL_H_

#include <string>
#include <cctype>
#include <algorithm>

namespace Hr
{
	class HrStringUtil
	{
	public:
		static void ToLowerCase(std::string& s)
		{
			std::transform(s.begin(), s.end(), s.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}

		static void ToUpperCase(std::string& s)
		{
			std::transform(s.begin(), s.end(), s.begin(),
				[](unsigned char c) { return std::toupper(c); });
		}
	};
}


#endif



