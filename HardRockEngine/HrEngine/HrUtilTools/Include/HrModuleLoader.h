#ifndef _HR_MODULELOADER_H_
#define _HR_MODULELOADER_H_

#include <string>

namespace Hr
{
	class HrModuleLoader
	{
	public:
		HrModuleLoader(const std::string& strModule, const std::string& strProName);
		~HrModuleLoader();

		bool HrLoadModule();
		void HrFreeModule();

		void* GetProcAddress();
	private:
		void* m_pModuleHandle;

		std::string m_strModule;
		std::string m_strProcName;
	};
}

#endif


