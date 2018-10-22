#ifndef _HR_D3D11SHADER_H_
#define _HR_D3D11SHADER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrD3D11Device.h"
#include <d3dcompiler.h>

namespace Hr
{
	class HrD3D11SRVShaderParamRelationShip
	{
	public:
		HrD3D11SRVShaderParamRelationShip(HrRenderEffectParameter* pTexParam, std::vector<ID3D11ShaderResourceView*>* pVecD3D11SRV, size_t nIndex)
			: m_pTextureParam(pTexParam), m_pVecD3D11SRV(pVecD3D11SRV), m_nPosIndex(nIndex)
		{}

		void UpdateShaderResourceView();
	protected:
		HrRenderEffectParameter* m_pTextureParam;
		std::vector<ID3D11ShaderResourceView*>* m_pVecD3D11SRV;
		size_t m_nPosIndex;
	};

	class HrD3D11SSShaderParamRelationShip
	{
	public:
		HrD3D11SSShaderParamRelationShip(HrRenderEffectParameter* pSamplerParam, std::vector<ID3D11SamplerState*>* pVecD3D11SS, size_t nIndex)
			: m_pSamplerParam(pSamplerParam), m_pVecD3D11SS(pVecD3D11SS), m_nPosIndex(nIndex)
		{}

		void UpdateSamplerState();
	protected:
		HrRenderEffectParameter* m_pSamplerParam;
		std::vector<ID3D11SamplerState*>* m_pVecD3D11SS;
		size_t m_nPosIndex;
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
		const std::vector<ID3D11ShaderResourceView*>& GetShaderResourceViews();
		const std::vector<ID3D11SamplerState*>& GetSamplerStates();
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
		std::vector<ID3D11SamplerState*> m_vecD3D11SamplerState;

		std::vector<HrD3D11SRVShaderParamRelationShip> m_vecSRVParamRelationships;
		std::vector<HrD3D11SSShaderParamRelationShip> m_vecSSParamRelationships;
	};
}

#endif







