#ifndef _HR_D3D11SHADER_H_
#define _HR_D3D11SHADER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/IShader.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11Shader : public IShader
	{
	public:
		HrD3D11Shader();
		~HrD3D11Shader();

		virtual void Bind(IRender* pRender) override;
		virtual void UnBind(IRender* pRender) override;

		ID3D11VertexShader* GetVSShader()
		{
			return m_pVSShader;
		}
		ID3D11PixelShader* GetPSShader()
		{
			return m_pPSShader;
		}

	private:
		ID3D11VertexShader* m_pVSShader;
		ID3D11PixelShader* m_pPSShader;
	};
}

#endif



