#ifndef _HR_UTIL_H_
#define _HR_UTIL_H_

#include <memory>
#include <boost/functional/hash.hpp>

namespace Hr
{
	typedef unsigned int ElementInt;

	template <ElementInt nDigit0, ElementInt nDigit1, ElementInt nDigit2, ElementInt nDigit3>
	struct MakeElement4
	{
		static ElementInt const value = (nDigit0 << 0) | (nDigit1 << 1) | (nDigit2 << 2) | (nDigit3 << 3);
	};

	template <ElementInt nDigit0, ElementInt nDigit1, ElementInt nDigit2>
	struct MakeElement3
	{
		static ElementInt const value = MakeElement4<nDigit0, nDigit1, nDigit2, 0>::value;
	};

	template <ElementInt nDigit0, ElementInt nDigit1>
	struct MakeElement2
	{
		static ElementInt const value = MakeElement3<nDigit0, nDigit1, 0>::value;
	};

	template <ElementInt nDigit0>
	struct MakeElement1
	{
		static ElementInt const value = MakeElement2<nDigit0, 0>::value;
	};

	//ÒýÓÃ×ÔKlayGE
	template <typename T, typename... Args>
	inline std::shared_ptr<T> MakeSharedPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	inline std::unique_ptr<T> MakeUniquePtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	inline size_t Hr_Hash_Value(const char* str)
	{
		//static boost::hash<std::string> string_hash;
		static std::hash<std::string> string_hash;
		return string_hash(str);
	}
}

#endif


