#include <windows.h>
#include "HrWinTools.h"
#include "HrConsole.h"

int WINAPI WinMain( HINSTANCE hInstance,	//��ǰʵ�����
	HINSTANCE hPrevInstance,                //ǰһ��ʵ�����
	LPSTR lpCmdLine,			            //�������ַ�
	int nCmdShow )			                //������ʾ��ʽ
{
	SetMyCurrentDirectory();
	
#ifdef _DEBUG
	CHrConsole::OpenConsole();
#endif // DEBUG




#ifdef _DEBUG
	CHrConsole::CloseConsole();
#endif // DEBUG

	return 0;
}


















