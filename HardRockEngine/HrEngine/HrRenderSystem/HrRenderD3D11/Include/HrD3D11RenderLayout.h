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

		virtual uint32 GetVertextSize() override;

		ID3D11InputLayout* GetInputLayout();
		ID3D11Buffer* GetVertexBuffer();
	private:
		ID3D11InputLayout* m_pInputLayout;

		ID3D11Buffer* m_pVertexBuffer;

	public:

		ID3D11VertexShader* m_pSolidColorVS;
		ID3D11PixelShader* m_pSolidColorPS;
	private:
		bool CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer);
	
		struct VertexPos
		{
			DirectX::XMFLOAT3 pos;
		};
	};
}

#endif





