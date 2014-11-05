#ifndef _HR_DEFINE_H_
#define _HR_DEFINE_H_


#ifndef AR
#define AR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }                 //自定义一个HR宏，方便执行错误的返回
#endif

#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = NULL; } }       //自定义一个SAFE_RELEASE()宏,便于指针资源的释放
#endif    

#ifndef SAFE_RELEASE			
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = NULL; } }       //自定义一个SAFE_RELEASE()宏,便于COM资源的释放
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    

#ifndef FAILED_RETURN
#define FAILED_RETURN(x)	{ if (FAILED(x)) { return FALSE; }}
#endif

#endif