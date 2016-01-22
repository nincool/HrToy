/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_DIRECTOR_H_
#define _HR_DIRECTOR_H_

#include "IDirector.h"

namespace Hr
{
	class ITimer;
	class HrSystemSupporter;

	class HR_CORE_API HrDirector : public IDirector
	{
	public:
		~HrDirector();

		virtual bool Init() override;
		virtual void StartMainLoop() override;
		virtual void End() override;
		virtual void Release() override;

		virtual bool Render() override;
		
	protected:
		HrDirector();

	private:
		bool m_bEndMainLoop;

	};

}

#endif





