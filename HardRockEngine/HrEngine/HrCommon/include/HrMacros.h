#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

//////////////////////////////////////////////////////////////////////////
//Macros
//////////////////////////////////////////////////////////////////////////
#define HR_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public:  varType Get##funName(void) const;

#define HR_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public:  const varType& Get##funName(void) const;

#define HR_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public:  varType Get##funName(void);\
public:  void Set##funName(varType var);

#define HR_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public:  const varType& Get##funName(void) const;\
public:  void Set##funName(const varType& var);

#define HR_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public:  varType Get##funName(void) const { return varName; }

#define HR_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public:  const varType& Get##funName(void) const { return varName; }

#define HR_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public:  varType Get##funName(void) const { return varName; }\
public:  void Set##funName(varType var){ varName = var; }

#define HR_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public:  const varType& Get##funName(void) const { return varName; }\
public:  void Set##funName(const varType& var){ varName = var; }

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);		(p)=NULL; } }
#endif

#define HR_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define HR_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define HR_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define HR_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)




#if (HR_DEBUG > 0)
#define HRLOG(format,...)      Hr::HrLog::Instance()->Log(Hr::HrLog::_HALL, format,  ##__VA_ARGS__)
#define HRWARNING(format,...)  Hr::HrLog::Instance()->Log(Hr::HrLog::_HWARNING, format,  ##__VA_ARGS__)
#define HRERROR(format,...)    Hr::HrLog::Instance()->Log(Hr::HrLog::_HERROR, format,  ##__VA_ARGS__)
#else
#define HRLOG(format,...)      
#define HRWARNING(format,...)  
#define HRERROR(format,...)   
#endif

#define HR_ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

#define HRASSERT(a, content, ...)  if (!a) Hr::HrLog::Instance()->Log(Hr::HrLog::_HERROR, content,  ##__VA_ARGS__); BOOST_ASSERT(a);

#if (HR_DEBUG > 0)

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
// Also hooks up the file/line/function params
// Can only be used with classes that derive from AllocatedObject since customised new/delete needed
#   define HR_NEW new 
#   define HR_DELETE delete

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif // SAFE_DELETE
#	define SAFE_DELETE(p) HR_DELETE p; p = nullptr
#else // !OGRE_DEBUG_MODE

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
#   define HR_NEW new 
#   define HR_DELETE delete

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif // SAFE_DELETE
#	define SAFE_DELETE(p) (HR_DELETE p; p = nullptr);
#endif // HR_DEBUG

#define HR_UNUSED(a) (void)(a)

#endif


