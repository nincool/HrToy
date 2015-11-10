#ifndef _HR_GAMEFRAMEWORK_H_
#define _HR_GAMEFRAMEWORK_H_

#include "HrFrameworkPrerequisites.h"
#include "IGameFramework.h"

namespace Hr
{
	class IDirector;
	class HrGameFramework : public IGameFramework
	{
	public:
		~HrGameFramework();

	public:
		virtual bool Init() override;
		virtual void Run() override;

		HR_INSTANCE(HrGameFramework);
	protected:
		HrGameFramework();
	private:
		HINSTANCE m_hHandleSystemCenter;

		IDirector* m_pDirector;
	};

}


#endif

