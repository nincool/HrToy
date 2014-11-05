#ifndef _HR_DEFINE_H_
#define _HR_DEFINE_H_


#ifndef AR
#define AR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }                 //�Զ���һ��HR�꣬����ִ�д���ķ���
#endif

#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = NULL; } }       //�Զ���һ��SAFE_RELEASE()��,����ָ����Դ���ͷ�
#endif    

#ifndef SAFE_RELEASE			
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = NULL; } }       //�Զ���һ��SAFE_RELEASE()��,����COM��Դ���ͷ�
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    

#ifndef FAILED_RETURN
#define FAILED_RETURN(x)	{ if (FAILED(x)) { return FALSE; }}
#endif

#endif