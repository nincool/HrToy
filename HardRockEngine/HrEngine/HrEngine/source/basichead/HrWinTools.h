#ifndef _HR_WINTOOLS_H_
#define _HR_WINTOOLS_H_

#include <windows.h>
#include <cassert>

bool EraseEndStringWithChar( char* p, char c )
{
	assert( p && "EraseEndStringWhithChar Error, the param is null" );

	char* pFlag = strrchr( p, c );
	if (pFlag != NULL)
	{
		*(pFlag) = '\0';

		return true;
	}

	return false;
}

/**
 *	@Brief: 设置工作目录 [2/27/2015 By Hr]
*/
bool SetMyCurrentDirectory()
{
	//设置工作目录
	char* pFlag = NULL;
	char szModuleDir[255];
	ZeroMemory( szModuleDir, sizeof( szModuleDir ) );

	GetModuleFileName( NULL, szModuleDir, sizeof( szModuleDir ) );
	bool b1 = EraseEndStringWithChar( szModuleDir, '\\' );
	bool b2 = EraseEndStringWithChar( szModuleDir, '\\' );
	if (b1 && b2)
		SetCurrentDirectory( szModuleDir );
	else
		return false;

	return true;
}



#endif //_HR_WINTOOLS_H_