#ifndef _HR_CONSOLE_H_
#define _HR_CONSOLE_H_

#include <stdio.h> 
#include <io.h> 
#include <fcntl.h> 
#include <Windows.h>
#include <tchar.h>


class CHrConsole
{
public:
	CHrConsole();
	~CHrConsole();

public:
	/*
		@brief	Open the Console [2/13/2015 By Hr] 	
	*/
	static void OpenConsole()
	{
		AllocConsole();										  //打开控制台窗口以显示调试信息  
		SetConsoleTitleA( "Debug Win Output" );            //设置标题  
		HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );      //获取控制台输出句柄  
		INT hCrt = _open_osfhandle( (INT)hCon, _O_TEXT );     //转化为C文件描述符  
		FILE * hf = _fdopen( hCrt, "w" );					  //转化为C文件流  
		//setvbuf( hf, NULL, _IONBF, 0 );                       //无缓冲  
		setvbuf( hf, szBuffer, _IOLBF, 1024 );                       //无缓冲 
		*stdout = *hf;										  //重定向标准输出  
	}

	/*
		@brief	Close the console [2/13/2015 By Hr] 	
	*/
	static void CloseConsole()
	{
		FreeConsole();
	}

	static char szBuffer[1024];
};

char CHrConsole::szBuffer[1024];

#endif
