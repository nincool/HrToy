#ifndef _HR_UTIL_H_
#define _HR_UTIL_H_

#include <memory>
#include <boost/functional/hash.hpp>
#include <boost/cast.hpp>


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
	inline std::shared_ptr<T> HrMakeSharedPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	inline std::unique_ptr<T> HrMakeUniquePtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	inline std::shared_ptr<T> MakeComPtr(T* p)
	{
		return p ? std::shared_ptr<T>(p, std::mem_fn(&T::Release)) : std::shared_ptr<T>();
	}

	inline size_t HrHashValue(const char* str)
	{
		//static boost::hash<std::string> string_hash;
		static std::hash<std::string> string_hash;
		return string_hash(str);
	}

	inline size_t HrHashValue(const std::string str)
	{
		//static boost::hash_range(str.begin(), str.end());
		static std::hash<std::string> string_hash;
		return string_hash(str);
	}

	template <typename T, typename U>
	inline std::shared_ptr<T> HrCheckPointerCast(U& u)
	{
		BOOST_ASSERT(std::dynamic_pointer_cast<T>(u) == std::static_pointer_cast<T>(u));
		return std::static_pointer_cast<T>(u);
	}

	template <typename T, typename U>
	inline std::shared_ptr<T> HrStaticPointerCast(U& u)
	{
		return std::static_pointer_cast<T>(u);
	}

	template <typename T, typename U>
	inline T* HrCheckPointerCast(U* p)
	{
		return boost::polymorphic_downcast<T*>(p);
	}

	template <typename T, typename U>
	inline T* HrStaticPointerCast(U* p)
	{
		return static_cast<T*>(p);
	}
}

#endif


