#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

//////////////////////////////////////////////////////////////////////////
//Macros
//////////////////////////////////////////////////////////////////////////
#define HR_INSTANCE(type) public: static type* GetInstance() {	if (m_s_pInstance == nullptr) { m_s_pInstance = HR_NEW type; } return m_s_pInstance; } \
	static void ReleaseInstance() { SAFE_DELETE(m_s_pInstance); } private: static type* m_s_pInstance;
#define HR_INSTANCE_DEF(type) type* type::m_s_pInstance = nullptr

#define HR_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const;

#define HR_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const;

#define HR_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void);\
public: virtual void Set##funName(varType var);

#define HR_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const;\
public: virtual void Set##funName(const varType& var);

#define HR_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }

#define HR_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const { return varName; }

#define HR_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }

#define HR_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const { return varName; }\
public: virtual void Set##funName(const varType& var){ varName = var; }

#define HR_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var)   \
{ \
	if (varName != var) \
							{ \
	CC_SAFE_RETAIN(var); \
	CC_SAFE_RELEASE(varName); \
	varName = var; \
							} \
} 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);		(p)=NULL; } }
#endif

#if (HR_DEBUG > 0)
#define HRLOG(format,...)      Hr::HrLog::GetInstance()->Log(Hr::ILog::_HALL, format,  ##__VA_ARGS__)
#define HRWARNING(format,...)  Hr::HrLog::GetInstance()->Log(Hr::ILog::_HWARNING, format,  ##__VA_ARGS__)
#define HRERROR(format,...)    Hr::HrLog::GetInstance()->Log(Hr::ILog::_HERROR, format,  ##__VA_ARGS__)
#else
#define HRLOG(format,...)      
#define HRWARNING(format,...)  
#define HRERROR(format,...)   
#endif

#include <assert.h>
#define HRASSERT(a, content, ...)  if (!a) Hr::HrLog::GetInstance()->Log(Hr::ILog::_HERROR, content,  ##__VA_ARGS__); assert(a);

#endif


