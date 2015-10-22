#include <windows.h>
#include "HrWinTools.h"
#include "HrConsole.h"
#include <time.h>
#include <iostream>
#include <boost/format.hpp>
#include "HrLog.h"
#include "HrMutexLock.h"
#include "HrEngineCommon.h"

using namespace std;                

void InitLogInfo()
{
	//初始化Log
	CHrLog::HrLogConf stHrLog;
	stHrLog.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;
	stHrLog.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;
	stHrLog.nLevelFlag = _HALL;
	char szModuleFilePath[255];
	HR_ZEROMEM( szModuleFilePath, sizeof( szModuleFilePath ) );
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
}

int WINAPI WinMain( HINSTANCE hInstance,	//当前实例句柄
	HINSTANCE hPrevInstance,                //前一个实例句柄
	LPSTR lpCmdLine,			            //命令行字符
	int nCmdShow )			                //窗口显示方式
{
	SetMyCurrentDirectory();
	InitLogInfo();

	//cout.rdbuf( CHrLog::pBuf );
	
	system("pause");
	return 0;
}











