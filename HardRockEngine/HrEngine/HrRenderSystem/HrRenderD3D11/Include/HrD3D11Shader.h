#ifndef _HR_D3D11SHADER_H_
#define _HR_D3D11SHADER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrD3D11Device.h"
#include <d3dcompiler.h>

namespace Hr
{
	class CHrD3D11SRVShaderParamRelationShip
	{
	public:
		CHrD3D11SRVShaderParamRelationShip(HrRenderEffectParameter* pTexParam, ID3D11ShaderResourceView** pD3D11SRV)
			: m_pTextureParam(pTexParam), m_pD3D11SRV(pD3D11SRV)
		{}

		void UpdateShaderResourceView();
	protected:
		HrRenderEffectParameter* m_pTextureParam;
		ID3D11ShaderResourceView** m_pD3D11SRV;
	};

	////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////
	

	class HrD3D11Shader : public HrShader, public std::enable_shared_from_this<HrD3D11Shader>
	{
	public:
		HrD3D11Shader();
		~HrD3D11Shader();

		virtual void Accept(const HrRenderPtr& pRender) override;

		virtual void Unaccept(const HrRenderPtr& pRender) override;

		virtual void StreamIn(const HrStreamDataPtr& pStreamBuf, const std::string& strFile, const std::string& strName, EnumShaderType shaderType) override;

		const HrStreamDataPtr& GetCodeData()
		{
			return m_pShaderBuffer;
		}

		const ID3D11VertexShaderPtr& GetVSShader()
		{
			return m_pVertexShader;
		}
		const ID3D11PixelShaderPtr& GetPSShader()
		{
			return m_pPixelShader;
		}

		const ID3D11VertexShaderPtr& RetriveD3D11VertexShader();
		const ID3D11PixelShaderPtr& RetriveD3D11PixelShader();

		const std::vector<ID3D11Buffer*>& GetConstBuffers();
		const std::vector<ID3D11ShaderResourceView*>& GetSRVs();
	protected:
		virtual void BindRenderParameterImpl() override;
	private:
		void CreateVertexShader();
		void CreatePixelShader();

	private:
		std::string m_strFilePath;

		HrStreamDataPtr m_pShaderBuffer;

		ID3D11VertexShaderPtr m_pVertexShader;
		ID3D11PixelShaderPtr m_pPixelShader;

		std::vector<ID3D11Buffer*> m_vecD3D11ConstBuffer;
		std::vector<ID3D11ShaderResourceView*> m_vecD3D11SRV;
		std::vector<ID3D11SamplerState*> m_vecSamplerState;

		std::vector<CHrD3D11SRVShaderParamRelationShip> m_vecSRVParamRelationships;
	};
}

#endif







