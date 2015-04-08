#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p != nullptr) { delete (p); (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p != nullptr) { delete[] (p); (p)=nullptr; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p != nullptr) { (p)->Release(); (p)=nullptr; } }
#endif

#ifndef FAILED_RETURN
#define FAILED_RETURN(x)	{ if (FAILED(x)) { return FALSE; }}
#endif

#define HR_ZEROMEM(p, len) memset(p, 0, len)
#define HR_CLEAN_CHAR_BUFFER(p) (*((char*)(p))='\0')


#endif




