#ifndef _HR_D3D11SHADER_H_
#define _HR_D3D11SHADER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrD3D11Device.h"
#include <d3dcompiler.h>

namespace Hr
{

	class HrD3D11Shader : public HrShader
	{
	public:
		HrD3D11Shader();
		~HrD3D11Shader();

		virtual void Bind(HrRender* pRender) override;

		virtual void UnBind(HrRender* pRender) override;

		virtual void StreamIn(HrStreamData& streamBuffer, std::string& strFile, EnumShaderType shaderType) override;

		virtual void UpdateParams(HrRenderFrameParameters& renderFrameParameters) override;

		HrStreamData* GetStream()
		{
			return m_pShaderBuffer;
		}

		ID3D11VertexShader* GetVSShader()
		{
			return m_pVertexShader;
		}
		ID3D11PixelShader* GetPSShader()
		{
			return m_pPixelShader;
		}

	private:
		//bool CompileShader(HrStreamData& streamData);

		void CreateVertexShader(HrStreamData& streamBuffer);
		void CreatePixelShader(HrStreamData& streamBuffer);

		ID3D11Buffer* GetConstantBuffer();

	private:
		std::string m_strFilePath;

		HrStreamData* m_pShaderBuffer;

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
	};
}

#endif







