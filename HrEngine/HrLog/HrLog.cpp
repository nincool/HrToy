#include "HrLog.h"
#include <stdio.h>
#include <sys/stat.h>
#include <io.h>
#include <string>
#include <time.h>
#include <stdarg.h>
#include "HrPlatformDef.h"
#include "HrMutexLock.h" 
#include <fcntl.h> 
#include <Windows.h>

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#include <sys/io.h>
#include <dirent.h>
#endif

CHrLog CHrLog::m_s_instance;

CHrLog::CHrLog(void)
{
	m_pMutex = new CHrMutexLock();

	memset(&m_stLogConf, 0, sizeof(HrLogConf));
	m_stLogConf.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;					//写入控制台 写入文件
	m_stLogConf.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;	//日期和模块
	m_stLogConf.nLevelFlag = _HERROR;
	memcpy(m_stLogConf.szLogFileName, "Default", HR_LOGFILENAME_LEN);
	memset(m_szLogFileNameWithDate, 0, sizeof(m_szLogFileNameWithDate));
}

CHrLog::~CHrLog(void)
{
	SAFE_DELETE(m_pMutex);
}

CHrLog& CHrLog::Instance()
{
	return m_s_instance;
}

void CHrLog::LogInit( HrLogConf& stLogConf )
{
	memcpy(&m_stLogConf, &stLogConf, sizeof(m_stLogConf));
	if (m_stLogConf.nFileFlag & _HLOG_CONSOLE)
	{
#ifdef _DEBUG												// Release版禁用  
		AllocConsole();										//打开控制台窗口以显示调试信息  
		SetConsoleTitleA("LogDebug Win Output");         //设置标题  
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);      //获取控制台输出句柄  
		INT hCrt = _open_osfhandle((INT)hCon, _O_TEXT);     //转化为C文件描述符  
		FILE * hf = _fdopen( hCrt, "w" );					//转化为C文件流  
		setvbuf( hf, NULL, _IONBF, 0);						//无缓冲  
		*stdout = *hf;										//重定向标准输出  
#endif  
	}

	Log(_HERROR, "HLOG", "Log Start! Log File:[%s]", stLogConf.szLogFileName);
}

void CHrLog::GetFileName()
{
	bool bNeedCreateNew = false;
	//首先看下当前是否第一次构建log文件 
	if (strlen(m_szLogFileNameWithDate) > 0)
	{
		//已经创建了 查看文件大小是否超标了

		struct STAT info;

		if (STAT(m_szLogFileNameWithDate, &info) != -1)
		{
			if (info.st_size >= HR_LOGMAXFILE_LEN)
			{
				bNeedCreateNew = true;
			}
			else
			{
				//还可以继续写
				return;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//得到今天的log文件
	std::vector< std::string > vecLogFileName;
	GetAllTodayLogFileNames(vecLogFileName);
	if (vecLogFileName.empty())
	{
		MakeFileName(m_szLogFileNameWithDate, m_stLogConf.szLogFileName, 1);
	}
	else
	{
		//当前已经超过10M 直接创建一个新的
		if (bNeedCreateNew)
		{
			MakeFileName(m_szLogFileNameWithDate, m_stLogConf.szLogFileName, vecLogFileName.size() + 1);

			return;
		}

		bool bFind = false;
		struct _stat info;
		//找到不到10兆的文件
		for (size_t i = 0; i < vecLogFileName.size(); ++i)
		{
			if (_stat(vecLogFileName[i].c_str(), &info) != -1)
			{
				if (info.st_size < HR_LOGMAXFILE_LEN)
				{
					bFind = true;
					memcpy(m_szLogFileNameWithDate, vecLogFileName[i].c_str(), HR_LOGFILENAME_LEN);
				}
			}
		}
		//找了一圈没找到 碰上了奇葩情况
		if (!bFind)
		{
			//直接创建一个新的
			MakeFileName(m_szLogFileNameWithDate, m_stLogConf.szLogFileName, vecLogFileName.size() + 1);
		}
	}
}

void CHrLog::GetAllTodayLogFileNames(std::vector< std::string >& vecLogFileName)
{
#ifdef WIN32
	_finddata_t stFile;
	long lf;
	if ((lf = _findfirst("*.Hlog", &stFile)) == -1)
	{
		//return;
	}
	else
	{
		//进行时间比较
		char szTodayBuf[HR_LABELBUFF_LEN];
		memset(szTodayBuf, 0, sizeof(szTodayBuf));
		time_t t;
		time(&t);
		struct tm stTm;
		LOCALTIME(&stTm, &t);
		strftime(szTodayBuf, HR_LABELBUFF_LEN, "[%Y/%m/%d]", &stTm);
		
		do 
		{
			char szFileCreateDateBuf[HR_LABELBUFF_LEN];
			memset(szFileCreateDateBuf, 0, sizeof(szFileCreateDateBuf));
			LOCALTIME(&stTm, &stFile.time_create);	//获取创建时间
			strftime(szFileCreateDateBuf, HR_LABELBUFF_LEN, "[%Y/%m/%d]", &stTm);

			if (strcmp(szTodayBuf, szFileCreateDateBuf) == 0)
			{
				vecLogFileName.push_back(stFile.name);
			}
		
		} while (_findnext(lf, &stFile) == 0);
	}

	_findclose(lf);
#else
	//进行时间比较
	char szTodayBuf[HR_LABELBUFF_LEN];
	memset(szTodayBuf, 0, sizeof(szTodayBuf));
	time_t t;
	time(&t);
	struct tm stTm;
	LOCALTIME(&stTm, &t);
	strftime(szTodayBuf, HR_LABELBUFF_LEN, "[%Y/%m/%d]", &stTm);
	
	DIR *pDirectory = NULL;
	struct dirent *pEntry = NULL;
	struct STAT info;
	pDirectory = opendir("./");
	if (pDirectory != NULL)
	{
		while (( pEntry = readdir(pDirectory)) != NULL)
		{
			//查找具体后缀名是Hlog的文件
			if (strstr(pEntry->d_name, ".Hlog") != NULL)
			{
				if (STAT(pEntry->d_name, &info) != -1)
				{
					char szFileCreateDateBuf[HR_LABELBUFF_LEN];
					memset(szFileCreateDateBuf, 0, sizeof(szFileCreateDateBuf));
					LOCALTIME(&stTm, &(info.st_ctim.tv_sec));
					strftime(szFileCreateDateBuf, HR_LABELBUFF_LEN, "[%Y/%m/%d]", &stTm);
					
					if (strcmp(szTodayBuf, szFileCreateDateBuf) == 0)
					{
						vecLogFileName.push_back(pEntry->d_name);
					}
				}
			}
		}
		closedir(pDirectory);
	}

#endif
}

void CHrLog::MakeFileName( char* pszNameWithDate, char* pszName , int nIndex)
{
	if (pszName == NULL || pszNameWithDate == NULL)
	{
		return;
	}

	char szTimeStarmp[HR_LABELBUFF_LEN];
	memset(szTimeStarmp, 0, sizeof(szTimeStarmp));
	MakeDateStarmp(szTimeStarmp, HR_LABELBUFF_LEN, '-');
	HrFormat(pszNameWithDate, HR_LOGFILENAME_LEN, "%s_%s_%d.Hlog", m_stLogConf.szLogFileName, szTimeStarmp, nIndex);
}
void CHrLog::MakeDateStarmp(char* pDateBuf, int nBufLen, char cSpace)
{
	time_t t;

	time(&t);
	struct tm stTm;
	LOCALTIME(&stTm, &t);
	if (cSpace == '-')
	{
		strftime(pDateBuf, nBufLen, "%Y-%m-%d", &stTm);
	}
	else
	{
		strftime(pDateBuf, nBufLen, "[[%Y/%m/%d]", &stTm);
	}
	
}

void CHrLog::MakeTimeStarmp( char* pTimeBuf, int nBufLen )
{
	time_t t;

	time(&t);
	struct tm stTm;
	LOCALTIME(&stTm, &t);
	strftime(pTimeBuf, nBufLen, "[%X]", &stTm);
}

void CHrLog::MakeFullTimeStarmp(char* pTimeBuf, int nBufLen)
{
	time_t t;

	time(&t);
	struct tm stTm;
	LOCALTIME(&stTm, &t);
	strftime(pTimeBuf, nBufLen, "[%Y/%m/%d %X] ", &stTm);
}

//-------------------------------------------------------------------------
//格式化字符串
//-------------------------------------------------------------------------
int CHrLog::HrFormat(char* pszBuf, int nMaxlength, char* pszFormat, ...)
{	
	int iListCount = 0;
	if (!pszBuf)
	{
		return iListCount;
	}

	va_list pArgList;
	//从此处开启系统循环，解析每条格式化输出的字符串
	va_start(pArgList, pszFormat);
	//返回格式化进去的字符数
	iListCount += VSNPRINTF(pszBuf + iListCount, nMaxlength - iListCount, (size_t)-1, pszFormat, pArgList);
	va_end(pArgList);

	if (iListCount > (nMaxlength - 1))
	{
		iListCount = nMaxlength - 1;
	}
	*(pszBuf + iListCount) = '\0';

	return iListCount;
}

void CHrLog::Log( unsigned int nLevel, char* pszModule, char* pszFormat, ... )
{
	char szLogBuff[HR_LOGFILEBUFF_LEN];
	memset(szLogBuff, 0, sizeof(szLogBuff));
	
	//首先检查是否初始化了 如果没有初始化 那么按照默认配置
	if (m_stLogConf.nLevelFlag > nLevel)
	{
		return;
	}

	//构建时间戳
	if (m_stLogConf.nFormatFlag & _HLOG_DATE || m_stLogConf.nFormatFlag & _HLOG_TIME)
	{
		char szTimeLavel[HR_LABELBUFF_LEN];
		memset(szTimeLavel, 0, sizeof(szTimeLavel));

		unsigned int iTimeFlag = m_stLogConf.nFormatFlag & (_HLOG_DATE | _HLOG_TIME);
		switch (iTimeFlag)
		{
		case 1:
			{
				MakeDateStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		case 2:
			{
				MakeTimeStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		case 3:
			{
				MakeFullTimeStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		}
		STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, szTimeLavel);
	}
	
	//构建模块等级
	unsigned int ret  = m_stLogConf.nFormatFlag & _HLOG_LEVEL;
	if (m_stLogConf.nFormatFlag & _HLOG_LEVEL)
	{
		char szLevelLabel[HR_LABELBUFF_LEN];
		memset(szLevelLabel, 0, sizeof(szLevelLabel));
		MakeLevelLabel(nLevel, szLevelLabel, HR_LABELBUFF_LEN);
		STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, szLevelLabel);
	}

	//构建模块自定义标签
	if (m_stLogConf.nFormatFlag & _HLOG_MODULE)
	{
		char szModuleLabel[HR_LABELBUFF_LEN];
		memset(szModuleLabel, 0, sizeof(szModuleLabel));
		szModuleLabel[0] = '[';
		memcpy(szModuleLabel+1, pszModule, HR_LABELBUFF_LEN-1);
		STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, szModuleLabel);
		STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, "] ");
	}

	int iListCount = 0;
	va_list  pArgList;
	char szLogContent[HR_LOGCONTENT_LEN];
	memset(szLogContent, 0, sizeof(szLogContent));

	va_start(pArgList, pszFormat);
	iListCount += VSNPRINTF(szLogContent, HR_LOGCONTENT_LEN, (size_t)-1, pszFormat, pArgList);
	va_end(pArgList);
	if (iListCount > (HR_LOGCONTENT_LEN - 1))
	{
		iListCount = HR_LOGCONTENT_LEN - 1;
	}
	szLogContent[iListCount] = '\0';
	STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, szLogContent);
	STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, "\n");

	//准备格式化进入文件
	if (m_stLogConf.nFileFlag & _HLOG_FILE)
	{
		FILE* fp = NULL;

		m_pMutex->Lock(); //加锁
		{
			GetFileName();
			//开始输出
			fp = fopen(m_szLogFileNameWithDate, "a+");
			if (fp)
			{
				iListCount = fprintf(fp, "%s", szLogBuff);
				fclose(fp);
			}
		}
		m_pMutex->UnLock();
	}

	//判断是否写入控制台
	if (m_stLogConf.nFileFlag & _HLOG_CONSOLE)
	{
		printf("%s", szLogBuff);
		//printf("sssss");
		fflush(stdout);
	}
}

void CHrLog::MakeLevelLabel( unsigned int nLevel, char* pszLabel, int nBufLen )
{
	if ( pszLabel )
	{
		switch (nLevel)
		{
		case _HALL:
			{
				memcpy(pszLabel, "[ALL]   ", nBufLen);
				break;
			}
		case _HDEBUG:
			{
				memcpy(pszLabel, "[DEBUG] ", nBufLen);
				break;
			}
		case _HNOTE:
			{
				memcpy(pszLabel, "[DEBUG] ", nBufLen);
				break;
			}
		case _HWARN:
			{
				memcpy(pszLabel, "[WARN]  ", nBufLen);
				break;
			}
		case _HERROR:
			{
				memcpy(pszLabel, "[ERROR] ", nBufLen);
				break;
			}
		}
	}
	
}

