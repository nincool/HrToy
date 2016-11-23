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

		virtual void StreamIn(HrStreamData& streamBuffer, const std::string& strFile, const std::string& strName, EnumShaderType shaderType) override;

		HrStreamData* GetCodeData()
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

	protected:
		virtual void BindRenderParameterImpl() override;
	private:
		void CreateVertexShader(HrStreamData& streamBuffer);
		void CreatePixelShader(HrStreamData& streamBuffer);

	private:
		std::string m_strFilePath;

		HrStreamData* m_pShaderBuffer;

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;

		std::vector<ID3D11Buffer*> m_vecD3D11ConstBuffer;
	};
}

#endif







