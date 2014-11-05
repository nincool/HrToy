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
	m_stLogConf.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;					//д�����̨ д���ļ�
	m_stLogConf.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;	//���ں�ģ��
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
#ifdef _DEBUG												// Release�����  
		AllocConsole();										//�򿪿���̨��������ʾ������Ϣ  
		SetConsoleTitleA("LogDebug Win Output");         //���ñ���  
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);      //��ȡ����̨������  
		INT hCrt = _open_osfhandle((INT)hCon, _O_TEXT);     //ת��ΪC�ļ�������  
		FILE * hf = _fdopen( hCrt, "w" );					//ת��ΪC�ļ���  
		setvbuf( hf, NULL, _IONBF, 0);						//�޻���  
		*stdout = *hf;										//�ض����׼���  
#endif  
	}

	Log(_HERROR, "HLOG", "Log Start! Log File:[%s]", stLogConf.szLogFileName);
}

void CHrLog::GetFileName()
{
	bool bNeedCreateNew = false;
	//���ȿ��µ�ǰ�Ƿ��һ�ι���log�ļ� 
	if (strlen(m_szLogFileNameWithDate) > 0)
	{
		//�Ѿ������� �鿴�ļ���С�Ƿ񳬱���

		struct STAT info;

		if (STAT(m_szLogFileNameWithDate, &info) != -1)
		{
			if (info.st_size >= HR_LOGMAXFILE_LEN)
			{
				bNeedCreateNew = true;
			}
			else
			{
				//�����Լ���д
				return;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�õ������log�ļ�
	std::vector< std::string > vecLogFileName;
	GetAllTodayLogFileNames(vecLogFileName);
	if (vecLogFileName.empty())
	{
		MakeFileName(m_szLogFileNameWithDate, m_stLogConf.szLogFileName, 1);
	}
	else
	{
		//��ǰ�Ѿ�����10M ֱ�Ӵ���һ���µ�
		if (bNeedCreateNew)
		{
			MakeFileName(m_szLogFileNameWithDate, m_stLogConf.szLogFileName, vecLogFileName.size() + 1);

			return;
		}

		bool bFind = false;
		struct _stat info;
		//�ҵ�����10�׵��ļ�
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
		//����һȦû�ҵ� �������������
		if (!bFind)
		{
			//ֱ�Ӵ���һ���µ�
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
		//����ʱ��Ƚ�
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
			LOCALTIME(&stTm, &stFile.time_create);	//��ȡ����ʱ��
			strftime(szFileCreateDateBuf, HR_LABELBUFF_LEN, "[%Y/%m/%d]", &stTm);

			if (strcmp(szTodayBuf, szFileCreateDateBuf) == 0)
			{
				vecLogFileName.push_back(stFile.name);
			}
		
		} while (_findnext(lf, &stFile) == 0);
	}

	_findclose(lf);
#else
	//����ʱ��Ƚ�
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
			//���Ҿ����׺����Hlog���ļ�
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
//��ʽ���ַ���
//-------------------------------------------------------------------------
int CHrLog::HrFormat(char* pszBuf, int nMaxlength, char* pszFormat, ...)
{	
	int iListCount = 0;
	if (!pszBuf)
	{
		return iListCount;
	}

	va_list pArgList;
	//�Ӵ˴�����ϵͳѭ��������ÿ����ʽ��������ַ���
	va_start(pArgList, pszFormat);
	//���ظ�ʽ����ȥ���ַ���
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
	
	//���ȼ���Ƿ��ʼ���� ���û�г�ʼ�� ��ô����Ĭ������
	if (m_stLogConf.nLevelFlag > nLevel)
	{
		return;
	}

	//����ʱ���
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
	
	//����ģ��ȼ�
	unsigned int ret  = m_stLogConf.nFormatFlag & _HLOG_LEVEL;
	if (m_stLogConf.nFormatFlag & _HLOG_LEVEL)
	{
		char szLevelLabel[HR_LABELBUFF_LEN];
		memset(szLevelLabel, 0, sizeof(szLevelLabel));
		MakeLevelLabel(nLevel, szLevelLabel, HR_LABELBUFF_LEN);
		STRCAT(szLogBuff, HR_LOGFILEBUFF_LEN, szLevelLabel);
	}

	//����ģ���Զ����ǩ
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

	//׼����ʽ�������ļ�
	if (m_stLogConf.nFileFlag & _HLOG_FILE)
	{
		FILE* fp = NULL;

		m_pMutex->Lock(); //����
		{
			GetFileName();
			//��ʼ���
			fp = fopen(m_szLogFileNameWithDate, "a+");
			if (fp)
			{
				iListCount = fprintf(fp, "%s", szLogBuff);
				fclose(fp);
			}
		}
		m_pMutex->UnLock();
	}

	//�ж��Ƿ�д�����̨
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

