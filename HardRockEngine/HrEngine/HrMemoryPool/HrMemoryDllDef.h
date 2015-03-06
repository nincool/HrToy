
#ifdef _HR_MEMORY_DLL_
#define HR_MEMORY_DLL	_declspec(dllexport)
#else
#define HR_MEMORY_DLL  _declspec(dllimport)
#endif
