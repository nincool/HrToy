#ifndef _HR_PLATFORM_H_
#define _HR_PLATFORM_H_


#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p != NULL) { delete (p); (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p != NULL) { delete[] (p); (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p != NULL) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef FAILED_RETURN
#define FAILED_RETURN(x)	{ if (FAILED(x)) { return FALSE; }}
#endif

#define HR_CLEAN_CHAR_BUFFER(p) (*((char*)(p))='\0')


#ifdef HR_WINDOWS 
#define	VSNPRINTF(pBuff, nBufLen, nCount, pFormat, pArglist)	vsnprintf_s(pBuff, nBufLen, nCount, pFormat, pArglist)
#define STRCAT(pBufDes, nBufLen, pBufSrc)						strcat_s(pBufDes, nBufLen, pBufSrc)
#define LOCALTIME(tm, t)										localtime_s(tm, t)
#define STRCPY(pBufDes, nBufLen, pBufSrc)						strcpy_s(pBufDes, nBufLen, pBufSrc)
#define STAT										_stat
#define FOPEN(pFile, pFileName, pModel)                         fopen_s(&pFile, pFileName, pModel)
#else
#define VSNPRINTF(pBuff, nBufLen, nCount, pFormat, pArglist)	vsnprintf(pBuff, nBufLen, pFormat, pArglist)
#define STRCAT(pBufDes, nBufLen, pBufSrc)						strcat(pBufDes, pBufSrc)
#define LOCALTIME(tm, t)										localtime_r(t, tm)
#define STRCPY(pBufDes, nBufLen, pBufSrc)						strcpy(pBufDes, pBufSrc)
#define STAT 										stat
#define FOPEN(pFile, pFileName, pModel)                         (pFile = fopen(pFileName, pModel))
#endif

#endif




