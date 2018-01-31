#ifndef _HR_D3D11RENDERLAYOUT_H_
#define _HR_D3D11RENDERLAYOUT_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

#include <DirectXMath.h>
using namespace DirectX;


namespace Hr
{
	class HrD3D11RenderLayout : public HrRenderLayout
	{
	public:
		HrD3D11RenderLayout();
		~HrD3D11RenderLayout();

		const ID3D11InputLayoutPtr& GetInputLayout(const HrD3D11ShaderPtr& pShader);
		const ID3D11BufferPtr& GetVertexBuffer();
		const ID3D11BufferPtr& GetIndexBuffer();
	private:
		D3D11_INPUT_ELEMENT_DESC* m_pD3DInputElementDesc;
		ID3D11InputLayoutPtr m_pD3DInputLayout;
		ID3D11Buffer* m_pD3DVertexBuffer;
	};
}

#endif





