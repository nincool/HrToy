#ifndef _HR_UTIL_H_
#define _HR_UTIL_H_

#include <memory>
#include <boost/functional/hash.hpp>
#include <boost/cast.hpp>

//置位特定位
#define   SET_NTH_BIT(x, n)                    ( x | ((1U)<<(n)) )
#define   SET_NTH_BIT64(x, n)                  ( x | (uint64(1)<<(n)) )
//置位n到m位				                  
#define   SET_BIT_N_TO_M(x,n,m)                ( x | (~((~0u)<<(m-n+1)))<<(n))
//复位特定位					              
#define   CLEAR_NTH_BIT(x, n)                  ( x & ~((1U)<<(n)) )
#define   CLEAR_NTH_BIT64(x, n)                ( x & ~(uint64(1)<<(n)) )
#define   CLEAR_BIT_N_TO_M(x,n,m)              ( x & ((~0u)<<(m-n+1))<<(n))
#define   CLEAR_BIT_N_TO_M64(x,n,m)            ( x & ((~0u)<<(m-n+1))<<(n))
//截取特定位						           
#define	  GETBIT(x, n)                         ( x & ((1u) << (n)))
#define   GETBIT64(x, n)                       ( x & (uint64(1) << (n)))

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

	//引用自KlayGE
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

	template <typename T>
	inline size_t HrHashValue(const T& p)
	{
		return boost::hash_value(p);
	}

	//template <>
	//inline size_t HrHashValue<std::string>(const std::string& str)
	//{
	//	static std::hash<std::string> string_hash;
	//	return string_hash(str);
	//}

	template <class T>
	inline void HrHashCombine(std::size_t& seed, T const& v)
	{
		return boost::hash_combine(seed, v);
	}

	template <typename T, typename U>
	inline std::shared_ptr<T> HrCheckPointerCast(const U& u)
	{
		BOOST_ASSERT(std::dynamic_pointer_cast<T>(u) == std::static_pointer_cast<T>(u));
		return std::static_pointer_cast<T>(u);
	}

	template <typename T, typename U>
	inline std::shared_ptr<T> HrStaticPointerCast(const U& u)
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

	/////////////////////////////////////////////////////////
	
}

#endif


