#pragma once

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��

// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��

#define _WIN32_WINNT 0x0501      //0x0501Ϊwindos xp
#define WINVER 0x0501

#ifndef WINVER                   //ָ��Ҫ������ƽ̨��windows vista
#define WINVER 0x0600
#endif

#ifndef _WIN32_WINNT             //ָ��Ҫ������ƽ̨�� windows vista
#define _WIN32_WINNT            
#endif

#ifndef _WIN32_WINDOWS           //ָ��Ҫ������ƽ̨�� windows 98
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE                //ָ��Ҫ������ƽ̨�� Internet Explorer 7.0
#define _WIN32_IE 0x0700
#endif

#include <SDKDDKVer.h>


