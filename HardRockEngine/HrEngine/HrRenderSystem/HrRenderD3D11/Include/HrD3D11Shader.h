#ifndef _HR_D3D11SHADER_H_
#define _HR_D3D11SHADER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11Shader : public HrShader
	{
	public:
		HrD3D11Shader();
		~HrD3D11Shader();

		virtual void Bind(IRender* pRender) override;
		virtual void UnBind(IRender* pRender) override;

		virtual void StreamIn(HrStreamData& streamData) override;

		ID3D11VertexShader* GetVSShader()
		{
			return m_pVertexShader;
		}
		ID3D11PixelShader* GetPSShader()
		{
			return m_pPixelShader;
		}

	private:
		bool CompileShader(HrStreamData& streamData);

		void CreateVertexShader();
		void CreatePixelShader();
	private:
		HrStreamData* m_pShaderBuffer;

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
	};
}

#endif



