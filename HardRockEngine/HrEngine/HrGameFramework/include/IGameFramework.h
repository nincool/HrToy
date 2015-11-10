/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/27/2015 By Hr]
*
************************************************************************/  
#ifndef _IGAMEFRAMEWORK_H_
#define _IGAMEFRAMEWORK_H_

namespace Hr
{
	class IGameFramework
	{
	public:
		virtual ~IGameFramework(){}

		virtual bool Init() = 0;
		virtual void Run() = 0;
	};
}


#endif








