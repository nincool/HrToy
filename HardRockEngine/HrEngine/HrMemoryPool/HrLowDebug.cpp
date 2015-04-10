#include "StdAfx.h"
#include "HrLowDebug.h"
#include <string>
#include <time.h>
#include <stdarg.h>
#include "HrMacros.h"
#include "HrPlatformMacros.h"

using namespace std;
using namespace HrPool;

CHrLowDebug::CHrLowDebug( char* szPathName, char* szAppName, bool  bPrint2TTYFlag )
{
	m_pLock = new CHrMutexLock();

	m_bPrint2TTYFlag = bPrint2TTYFlag;

	char szModuleFilePath[255];
	HR_ZEROMEM( szModuleFilePath, sizeof( szModuleFilePath ) );
	GetModuleFileName( NULL, szModuleFilePath, sizeof( szModuleFilePath ) );
	char* pFilePath = strrchr( szModuleFilePath, '\\' );
	if (pFilePath != NULL)
	{
		*pFilePath = '\0';
	}

	if (szAppName)
	{
		MakeFullName( szModuleFilePath, szAppName, m_szFileName, "dbg" );
	}
	else
	{
		m_szFileName[0] = '\0';
	}

	DeleteAFile(m_szFileName);
	Debug2File("HrLowDebug:Start\n");
}

CHrLowDebug::~CHrLowDebug( void )
{
	SAFE_DELETE( m_pLock );
}

#ifdef HR_WIN
#define PATH_CHAR ("\\")
#else //not WIN32
#define PATH_CHAR ("/")
#endif
#define FILENAME_STRING_LENGTH 256   //�ļ�������ͳһΪ256

//-------------------------------------------------------------------------
// �õ�������·����
//-------------------------------------------------------------------------
void CHrLowDebug::MakeFullName( char* path, char* name, char* fullname, char* ext_name )
{
	if (strlen(path))	//���·����Ϊ��
	{
		if (strlen(ext_name))  //�������չ��
		{
			SafePrint(fullname, FILENAME_STRING_LENGTH, "%s%s%s.%s", path, PATH_CHAR, name, ext_name);
		}
		else
		{
			SafePrint(fullname, FILENAME_STRING_LENGTH, "%s%s%s", path, PATH_CHAR, name);
		}
	}
	else
	{
		if (strlen(ext_name))
		{
			SafePrint(fullname, FILENAME_STRING_LENGTH, "%s.%s", name, ext_name);
		}
		else
		{
			SafePrint(fullname, FILENAME_STRING_LENGTH, "%s", name);
		}
	}
}

void CHrLowDebug::DeleteAFile( char* szFileName )
{
	remove(szFileName);
}

char* CHrLowDebug::GetTrueFileName( char* szBuffer )
{
	int i = 0;

	char* pRet = szBuffer;
	int iLen = strlen(szBuffer);
	for (i = iLen-1; i >= 0; i--)
	{
		if ('\\' == *(szBuffer + i))		//windows·�������
		{
			pRet = (szBuffer + i + 1);
			break;
		}
		if ('/' == *(szBuffer + i))        //linux·�������
		{
			pRet = (szBuffer + i + 1);
			break;
		}
	}

	return pRet;
}

int CHrLowDebug::Debug2File( char* szFormat, ... )
{
	char szBuf[DEBUG_BUFFER_LENGTH];			//׼�����buffer
	char szTemp[DEBUG_BUFFER_LENGTH];			//ʱ����û����м�buffer
	char szTime[DEBUG_BUFFER_LENGTH];			//ʱ�����buffer


	int iListCount = 0;
	va_list  pArgList;
	
	//����ʱ���
	time_t t;
	struct tm TM;
	
	time(&t);
	LOCALTIME( &TM, &t );
	//localtime_s( pTM, &t );
	strftime( szTemp, DEBUG_BUFFER_LENGTH, "%Y/%m/%d %A %X", &TM );
	
	SafePrint(szTime, DEBUG_BUFFER_LENGTH, "[%s]", szTemp);

	m_pLock->Lock();
	{
		va_start(pArgList, szFormat);
		iListCount = VSNPRINTF( szBuf, DEBUG_BUFFER_LENGTH, DEBUG_BUFFER_LENGTH, szFormat, pArgList );
		va_end(pArgList);

		if (iListCount > (DEBUG_BUFFER_LENGTH - 1))
		{
			iListCount = DEBUG_BUFFER_LENGTH - 1;
		}

		//*(szBuf + iListCount) = '\n';
		*(szBuf + iListCount) = '\0';
		//��ʼ���
		FILE* fp = NULL;
		FOPEN( fp, m_szFileName, "a+" );
		setvbuf( fp, NULL, _IONBF, 0 );
		if (fp)
		{
			iListCount = fprintf(fp, "%s%s", szTime, szBuf);

			if (m_bPrint2TTYFlag)
			{
				printf("%s %s", szTime, szBuf);
			}
			
			fclose(fp);
		}
		else
		{
			iListCount = 0;
		}
	}
	m_pLock->UnLock();
	
	return iListCount;
}

//-------------------------------------------------------------------------
//��ʽ���ַ���
//-------------------------------------------------------------------------
int CHrLowDebug::SafePrint( char* szBuf, int iMaxlength, char* szFormat, ... )
{	
	if (!szBuf)
		goto SafePrint_END_PROCESS;

	int iListCount = 0;
	va_list pArgList;
	//�Ӵ˴�����ϵͳѭ��������ÿ����ʽ��������ַ���
	va_start(pArgList, szFormat);
	//���ظ�ʽ����ȥ���ַ���
	iListCount += VSNPRINTF(szBuf , iMaxlength ,iMaxlength, szFormat, pArgList);
	va_end(pArgList);

	if (iListCount > (iMaxlength - 1))
	{
		iListCount = iMaxlength - 1;
	}
	*(szBuf + iListCount) = '\0';

SafePrint_END_PROCESS:
	return iListCount;
}



void CHrLowDebug::Debug2File4Bin( char* pBuffer, int iLength )
{

}
