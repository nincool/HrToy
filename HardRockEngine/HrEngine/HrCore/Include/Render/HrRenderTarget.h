#ifndef _HR_RENDERTARGET_H_
#define _HR_RENDERTARGET_H_

#include "HrCore/Include/Render/IRenderTarget.h"

namespace Hr
{
	class HR_CORE_API HrRenderTarget : public IRenderTarget
	{
	public:
		HrRenderTarget();
		~HrRenderTarget();

		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc) override;
		virtual void AddViewPort(HrViewPort* pViewPort) override;
		virtual std::map<int, HrViewPort*>& GetViewPorts() override;

	protected:
		std::map<int, HrViewPort*> m_mapViewPort;
	};
}

#endif



