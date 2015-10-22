#ifndef _HR_CONSOLE_H_
#define _HR_CONSOLE_H_

namespace Hr
{


	class CHrConsole
	{
	public:
		CHrConsole();
		~CHrConsole();
		/// The max length of CCLog message.
		static const int MAX_LOG_LENGTH = 16 * 1024;

		static void Log(const char* pFormat, ...);
	};
}


#endif // !_HR_CONSOLE_H_


