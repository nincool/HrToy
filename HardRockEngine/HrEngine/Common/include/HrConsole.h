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
		AllocConsole();										  //�򿪿���̨��������ʾ������Ϣ  
		SetConsoleTitleA( "Debug Win Output" );            //���ñ���  
		HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );      //��ȡ����̨������  
		INT hCrt = _open_osfhandle( (INT)hCon, _O_TEXT );     //ת��ΪC�ļ�������  
		FILE * hf = _fdopen( hCrt, "w" );					  //ת��ΪC�ļ���  
		setvbuf( hf, NULL, _IONBF, 0 );                       //�޻���  
		*stdout = *hf;										  //�ض����׼���  
	}

	/*
		@brief	Close the console [2/13/2015 By Hr] 	
	*/
	static void CloseConsole()
	{

		FreeConsole();

	}

};

#endif
