#ifndef _HR_PLATFORMMACROS_H_
#define _HR_PLATFORMMACROS_H_


#ifdef HR_WIN
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

