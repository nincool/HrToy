#ifndef _HR_STRINGUTIL_H_
#define _HR_STRINGUTIL_H_

#include "HrPlatformConfig.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>

namespace Hr
{
	class HrStringUtil
	{
	public:
		static void Trim(HrString& str, bool left = true, bool right = true)
		{
			static const HrString delims = _T(" \t\r");
			if (right)
				str.erase(str.find_last_not_of(delims) + 1); // trim right
			if (left)
				str.erase(0, str.find_first_not_of(delims)); // trim left
		}

		static HrString Format(const TCHAR* pFormat, ...)
		{
#define HR_MAX_STRING_FORMAT_LENGTH (10 * 256)

			HrString rt;

			va_list ap;
			va_start(ap, pFormat);

			TCHAR szBuffer[HR_MAX_STRING_FORMAT_LENGTH];
			memset(szBuffer, 0, HR_MAX_STRING_FORMAT_LENGTH);
			int nCount = _vstprintf(szBuffer, pFormat, ap);
			if (nCount == -1 || nCount >= HR_MAX_STRING_FORMAT_LENGTH)
			{
				szBuffer[HR_MAX_STRING_FORMAT_LENGTH - 1] = '\0';
			}
			rt = szBuffer;

			return rt;
		}
	};
}


#endif

