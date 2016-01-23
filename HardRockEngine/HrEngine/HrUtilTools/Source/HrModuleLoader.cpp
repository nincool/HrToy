#include "HrModuleLoader.h"
#include "HrCommon/Include/HrPlatformConfig.h"

using namespace Hr;

// shared lib access define
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
#if (HR_DEBUG > 0)
#define HR_PREFIX ("")
#define HR_SUFFIX ("D.dll")
#else
#define HR_PREFIX _T("")
#define HR_SUFFIX _T(".dll")
#endif

#else //HR_TARGET_PLATFORM

#endif

HrModuleLoader::HrModuleLoader(const std::string& strModule, const std::string& strProName)
{
	m_pModuleHandle = nullptr;
	m_strModule = strModule;
	m_strModule.append(HR_SUFFIX);
	m_strProcName = strProName;
}

HrModuleLoader::~HrModuleLoader()
{
}

bool HrModuleLoader::HrLoadModule()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	m_pModuleHandle = LoadLibraryExA(m_strModule.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	return (m_pModuleHandle != nullptr);
#else
	return false;
#endif
	
}

void HrModuleLoader::HrFreeModule()
{
	if (m_pModuleHandle != nullptr)
	{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		::FreeLibrary(static_cast<HMODULE>(m_pModuleHandle));
#else
#endif
	}
}

void* HrModuleLoader::GetProcAddress()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	return reinterpret_cast<void*>(::GetProcAddress(static_cast<HMODULE>(m_pModuleHandle), m_strProcName.c_str()));
#else
	return nullptr;
#endif

}

