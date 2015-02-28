#pragma once
#include "HrMutexLock.h"

#define DEBUG_BUFFER_LENGTH			1024    //debug缓冲区大小
#define HR_DEBUG_FILENAME_LENGTH	256		//文件名长

namespace HrPool
{
	class HrLowDebug
	{
	public:
		HrLowDebug( char* szPathName, char* szAppName, bool  bPrint2TTYFlag = false );
		~HrLowDebug( void );

	public:
		static void		DeleteAFile( char* szFileName );
		static char*	GetTrueFileName( char* szBuffer );

	public:
		int				Debug2File( char* szFormat, ... );
		void			Debug2File4Bin( char* pBuffer, int iLength );

	private:
		/*
		@param		path 文件路径	name 文件名字	fullname 完整的路径 ext_name 后缀名
		@return	void
		@brief		格式化字符串功能
		*/
		void			MakeFullName( char* path, char* name, char* fullname, char* ext_name );
		/*
		@brief szBuf 用户指定的缓冲区 iMaxlength用户指定的缓冲区的大小 szFormat格式化输出字符串
		*/
		int				SafePrint( char* szBuf, int iMaxlength, char* szFormat, ... );
	private:
		bool			m_bPrint2TTYFlag;
		char			m_szFileName[HR_DEBUG_FILENAME_LENGTH];
		CHrMutexLock	m_Lock;
	};

}
