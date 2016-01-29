#ifndef _HR_MODULELOADER_H_
#define _HR_MODULELOADER_H_

#include <string>

namespace Hr
{
	class HrModuleLoader
	{
	public:
		HrModuleLoader(const std::string& strModule);
		~HrModuleLoader();

		bool HrLoadModule();
		void HrFreeModule();

		void* GetProcAddress(std::string strFuncName);
	private:
		void* m_pModuleHandle;

		std::string m_strModule;
	};
}

#endif


