#ifndef _HR_THROWEXCEPTION_H_
#define _HR_THROWEXCEPTION_H_

#include <string>
#include <stdexcept>
#include <system_error>

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef long HRESULT;
#endif

#define TIF(x) {HRESULT hr = x; if (static_cast<HRESULT>(hr) < 0){throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__));}}
#define TRE(x) {{throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":" + x);}}

#endif



