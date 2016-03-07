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

		ID3D11InputLayout* GetInputLayout(HrD3D11Shader* pShader);
		ID3D11Buffer* GetVertexBuffer();

	public:

		ID3D11VertexShader* m_pSolidColorVS;
		ID3D11PixelShader* m_pSolidColorPS;
	private:
		bool CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer);
	private:
		D3D11_INPUT_ELEMENT_DESC* m_pD3DInputElementDesc;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;
	};
}

#endif





