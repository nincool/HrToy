#ifndef _HR_UTIL_H_
#define _HR_UTIL_H_

#include <memory>

namespace Hr
{
	//ÒýÓÃ×ÔKlayGE
	template <typename T, typename... Args>
	inline std::shared_ptr<T> MakeSharedPtr(Args&& ... args)
	{
		//return std::shared_ptr<T>(new T(std::forward<Args>(args)...), std::default_delete<T>());
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	inline std::unique_ptr<T> MakeUniquePtr(Args&& ... args)
	{
		//return std::unique_ptr<T>(new T(std::forward<Args>(args)...), std::default_delete<T>());
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

#endif


