#include "stdafx.h"
#include <windows.h>
#include "HrWinTools.h"
#include "HrConsole.h"
#include "debug_new/HrNew.h"
#include <time.h>
#include <iostream>
#include <boost/format.hpp>

#include "debug_new/DebugNew_impl.h"

#include "HrLog.h"


using namespace std;




int WINAPI WinMain( HINSTANCE hInstance,	//��ǰʵ�����
	HINSTANCE hPrevInstance,                //ǰһ��ʵ�����
	LPSTR lpCmdLine,			            //�������ַ�
	int nCmdShow )			                //������ʾ��ʽ
{
	SetMyCurrentDirectory();
	
	//��ʼ��Log
	CHrLog::HrLogConf stHrLog;
	stHrLog.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;
	stHrLog.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;
	stHrLog.nLevelFlag = _HDEBUG;
	char szModuleFilePath[255];
	::ZeroMemory( szModuleFilePath, sizeof( szModuleFilePath ) );
	GetModuleFileName( NULL, szModuleFilePath, sizeof( szModuleFilePath ) );
	char* pFilePath = strrchr( szModuleFilePath, '\\' );
	if (pFilePath != NULL)
	{
		*pFilePath = '\0';
	}
	boost::format fmt( "%1%\\%2%" );
	fmt % szModuleFilePath % "HLog.log";
	std::string str = fmt.str();
	memcpy( stHrLog.szLogFileName, str.c_str(), sizeof( stHrLog.szLogFileName ) );
	HLog.LogInit( stHrLog );

	HLog.Log( _HDEBUG, "HR", "THIS IS A TEST LOG" );
	
	return 0;
}

















