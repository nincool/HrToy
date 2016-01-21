#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisites.h"
#include "HrRenderSystem/HrRenderCommon/IRender.h"

namespace Hr
{
	class IDirector;
	class HrD3D11Device;
	class IRenderDemo;

	class HrD3D11Render : public IRender
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
#else
		virtual bool Init(unsigned int nWidth, unsigned int nHeight) override;
#endif

		virtual void Release() override;
		virtual bool StartRender() override;

		HR_INSTANCE(HrD3D11Render);

	public:
		virtual void Render(const HrRenderTechnique* pRenderTechnique, const HrRenderLayout* pRenderLayout) override;
		/////////////////////////////--- RenderTest ---/////////////////////////////////
	public:
		IRenderDemo* m_pRenderDemo;

	private:
		//IHRD3D11DeviceContext* GetImmediateContext()
		//{
		//	if (m_pImmediateContext == nullptr)
		//	{
		//		m_pImmediateContext = HrD3D11Device::GetInstance()->GetImmediateContext();
		//	}
		//	return m_pImmediateContext;
		//}

	private:
		IHRD3D11DeviceContext* m_pImmediateContext;
	};
}


#endif

