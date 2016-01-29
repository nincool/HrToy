#ifndef _HR_D3D11RENDERLAYOUT_H_
#define _HR_D3D11RENDERLAYOUT_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/IRenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RenderLayout : public IRenderLayout
	{
	public:
		HrD3D11RenderLayout();

		ID3D11InputLayout* GetInputLayout();
		ID3D11Buffer* GetVertexBuffer();
	private:
		ID3D11InputLayout* m_pInputLayout;

		ID3D11Buffer* m_pVertexBuffer;

	};
}

#endif





