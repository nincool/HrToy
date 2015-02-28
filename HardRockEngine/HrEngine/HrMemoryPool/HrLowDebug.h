#pragma once
#include "HrMutexLock.h"

#define DEBUG_BUFFER_LENGTH			1024    //debug��������С
#define HR_DEBUG_FILENAME_LENGTH	256		//�ļ�����

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
		@param		path �ļ�·��	name �ļ�����	fullname ������·�� ext_name ��׺��
		@return	void
		@brief		��ʽ���ַ�������
		*/
		void			MakeFullName( char* path, char* name, char* fullname, char* ext_name );
		/*
		@brief szBuf �û�ָ���Ļ����� iMaxlength�û�ָ���Ļ������Ĵ�С szFormat��ʽ������ַ���
		*/
		int				SafePrint( char* szBuf, int iMaxlength, char* szFormat, ... );
	private:
		bool			m_bPrint2TTYFlag;
		char			m_szFileName[HR_DEBUG_FILENAME_LENGTH];
		CHrMutexLock	m_Lock;
	};

}
