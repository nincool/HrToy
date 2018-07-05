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
		const std::vector<ID3D11Buffer*>& GetD3DVertexBuffers();
		const std::vector<UINT>& GetStrides();
		const std::vector<UINT>& GetOffsets();

		virtual void Active() override;

	private:
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_vecInputElementDesc;
		std::vector<std::pair<size_t, ID3D11InputLayoutPtr> > m_vecInputLayouts;
		std::vector<ID3D11Buffer*> m_vecD3DVertexBuffer;
		std::vector<UINT> m_vecStrides;
		std::vector<UINT> m_vecOffsets;
	};
}

#endif





