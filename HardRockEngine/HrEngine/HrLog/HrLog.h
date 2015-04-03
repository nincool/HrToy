#ifndef _HR_LOG_H_
#define _HR_LOG_H_

#include <vector>
#include "HrLogDllDef.h"
#include <stdio.h> 
#include <iosfwd>

#define _HLOG_CONSOLE		0x01
#define _HLOG_FILE			0x02
#define _HLOG_FILE_DAILY	0x03            //暂时无用 
#define _HLOG_SYSLOG		0x04            //暂时无用
#define _HLOG_SIZE			0x05            //暂时无用

#define _HLOG_DATE			0x01
#define _HLOG_TIME			0x02
#define _HLOG_LEVEL			0x04
#define _HLOG_THREAD_ID		0x08            //暂时无用
#define _HLOG_MODULE		0x10
#define _HLOG_MESSAGE		0x20            //暂时无用
#define _HLOG_HEX			0x40            //暂时无用

#define _HALL				0
#define _HDEBUG				1
#define _HNOTE				10
#define _HWARN				15
#define _HERROR				20

#define HR_LOGFILENAME_LEN	260				//文件名长度
#define HR_LABELBUFF_LEN	32				//log等级标签长度			
#define HR_LOGFILEBUFF_LEN	512 			//缓冲区大小
#define HR_LOGCONTENT_LEN	480

#define HR_LOGMAXFILE_LEN	10485760		//10M

//尽量不要包含头文件
class CHrMutexLock;

class HR_LOG_DLL CHrLog
{
public:
	CHrLog(void);
	~CHrLog(void);

public:
	typedef struct HrLogConf
	{
		unsigned int		nFileFlag;
		unsigned int		nLevelFlag;
		unsigned int		nFormatFlag;
		char			    szLogFileName[HR_LOGFILENAME_LEN];
	};

	static std::streambuf* pBuf;
public:
	static CHrLog&		Instance();
public:
	void				LogInit(HrLogConf& stLogConf);

	/*
		@brief			log输入函数 [9/20/2013 By Hr] 	
	*/
	void				Log(unsigned int nLevel, char* pszModule, char* pszFormat, ...);
private:
	/*
		@brief			创建一个时间戳 [9/20/2013 By Hr] 	
	*/
	void				MakeDateStarmp(char* pDateBuf, int nBufLen, char cSpace = '/');
	void				MakeTimeStarmp(char* pTimeBuf, int nBufLen);
	void				MakeFullTimeStarmp(char* pTimeBuf, int nBufLen);
	/*
		@brief	       格式化函数  [9/21/2013 By Hr] 	
	*/
	int					HrFormat(char* pszBuf, int nMaxlength, char* pszFormat, ...);
	/*
		@brief	       输出等级标签 [9/21/2013 By Hr] 	
	*/
	void				MakeLevelLabel(unsigned int nLevel, char* pszLabel, int nBufLen);

	void				GetFileName();
	void				MakeFileName(char* pszNameWithDate, char* pszName, int nIndex);
	void				GetAllTodayLogFileNames(std::vector< std::string >& vecLogFileName);
private:
	static	CHrLog		m_s_instance;
private:
	HrLogConf			m_stLogConf;
	char				m_szLogFileNameWithDate[HR_LOGFILENAME_LEN];

	CHrMutexLock*		m_pMutex;

#define HLog			CHrLog::Instance() 
};

#endif
