#ifndef _HR_RENDERTARGET_H_
#define _HR_RENDERTARGET_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderTarget 
	{
	public:
		HrRenderTarget();
		virtual ~HrRenderTarget();

		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight);
		
		virtual void AddViewPort(HrViewPort* pViewPort);
		
		virtual std::map<int, HrViewPort*>& GetViewPorts();

	protected:
		//当前的视口集合
		std::map<int, HrViewPort*> m_mapViewPort;
	};
}

#endif



