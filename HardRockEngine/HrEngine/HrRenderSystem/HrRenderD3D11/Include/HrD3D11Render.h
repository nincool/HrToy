#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrRenderSystem/HrRenderCommon/IRender.h"

namespace Hr
{
	class IDirector;
	class HrD3D11Device;

	class HrD3D11Render : public IRender
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
		virtual void Release() override;
		virtual bool StartRender() override;


	public:
		//virtual void Render(const HrRenderTechnique* pRenderTechnique, const HrRenderLayout* pRenderLayout) override;

	private:
		void CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);
	
		/////////////////////////////--- RenderTest ---/////////////////////////////////
	public:
		//IRenderDemo* m_pRenderDemo;

	private:
		//IHRD3D11DeviceContext* GetImmediateContext()
		//{
		//	if (m_pImmediateContext == nullptr)
		//	{
		//		m_pImmediateContext = HrD3D11Device::GetInstance()->GetImmediateContext();
		//	}
		//	return m_pImmediateContext;
		//}
	};
}


#endif

