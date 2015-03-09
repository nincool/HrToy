
#ifdef _HR_LOG_DLL_
#define HR_LOG_DLL	_declspec(dllexport)
#else
#define HR_LOG_DLL  _declspec(dllimport)
#endif
