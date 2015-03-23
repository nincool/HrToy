#ifndef _HR_SINGLETON_H_
#define _HR_SINGLETON_H_

#include <memory>

template<typename T>
class CHrSingleTon < T >
{
public:
	static std::unique_ptr<T>& Instance()
	{
		return m_s_pUniquePtr;
	}

private:
	CHrSingleTon<T>(){};
	CHrSingleTon( const CHrSingleTon& );
	CHrSingleTon& operator=(const CHrSingleTon&);

	~CHrSingleTon(){};

	static std::unique_ptr<T> m_s_pUniquePtr;
};

template <typename T>
std::unique_ptr<T> CHrSingleTon<T>::m_s_pUniquePtr;


#endif