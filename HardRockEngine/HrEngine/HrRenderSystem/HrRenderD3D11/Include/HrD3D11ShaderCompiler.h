#ifndef _HR_D3D11SHADERCOMPILER_H_
#define _HR_D3D11SHADERCOMPILER_H_

#include "HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Asset/HrShaderCompiler.h"
#include "HrCore/Include/Render/HrShader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include <d3dcompiler.h>

namespace Hr
{

	struct D3D11ShaderDesc
	{
		D3D11ShaderDesc()
			: num_samplers(0), num_srvs(0), num_uavs(0), shaderType(HrShader::ST_VERTEX_SHADER)
		{
		}

		struct ConstantBufferDesc
		{
			ConstantBufferDesc()
				: size(0)
			{
			}

			struct VariableDesc
			{
				std::string name;
				size_t name_hash;
				uint32 size;

				std::string typeName;
				uint32 start_offset;
				uint32 varClass;
				uint32 type;
				uint32 rows;
				uint32 columns;
				uint32 elements;
				bool bUsed;

				std::vector<VariableDesc> struct_desc;
			};
			std::vector<VariableDesc> var_desc;

			std::string name;
			size_t name_hash;
			uint32_t size;
		};
		std::vector<ConstantBufferDesc> cb_desc;

		uint16_t num_samplers;
		uint16_t num_srvs;
		uint16_t num_uavs;

		struct BoundResourceDesc
		{
			std::string name;
			size_t name_hash;
			uint8_t type;
			uint8_t dimension;
			uint16_t bind_point;
		};
		std::vector<BoundResourceDesc> res_desc;

		HrShader::EnumShaderType shaderType;
	};

	class HrD3D11IncludeShaderHandler : public ID3DInclude
	{
	public:
		HrD3D11IncludeShaderHandler(std::string& strFile)
			: m_strFile(strFile) {}
		~HrD3D11IncludeShaderHandler() {}

		STDMETHOD(Open)(D3D_INCLUDE_TYPE IncludeType,
			LPCSTR pFileName,
			LPCVOID pParentData,
			LPCVOID *ppData,
			UINT *pByteLen
			)
		{
			// find & load source code
			HrStreamDataPtr pStreamData = HrFileUtils::Instance()->GetFileData(pFileName);
			// copy into separate c-string
			// Note - must NOT copy the null terminator, otherwise this will terminate
			// the entire program string!
			*pByteLen = static_cast<UINT>(pStreamData->GetBufferSizeWithoutNULLTerminator());
			char* pChar = new char[*pByteLen];
			memcpy(pChar, pStreamData->GetBufferPoint(), *pByteLen);
			*ppData = pChar;

			return S_OK;
		}

		STDMETHOD(Close)(LPCVOID pData)
		{
			char* pChar = (char*)pData;
			delete[] pChar;
			return S_OK;
		}
	protected:
		std::string m_strFile;

	};

	class HrD3D11ShaderCompiler : public HrShaderCompiler
	{
	public:
		HrD3D11ShaderCompiler();
		~HrD3D11ShaderCompiler();

		virtual bool CompileShaderFromCode(std::string& strShaderFileName, HrStreamData& streamData
			, HrShader::EnumShaderType shaderType
			, const std::string& strEntryPoint
			, HrStreamData& shaderBuffer) override;


		virtual bool ReflectEffectParameters(HrStreamData& shaderBuffer, const std::string& strShaderEntryPoint, HrShader::EnumShaderType shaderType) override;

		virtual bool StripCompiledCode(HrStreamData& shaderBuffer) override;

		virtual void CreateEffectParameters(std::vector<HrRenderEffectParameter*>& vecParameter
			, std::vector<HrRenderEffectStructParameter*>& vecRenderEffectStruct
			, std::vector<HrRenderEffectConstantBuffer*>& vecConstantBuffer) override;

		virtual void BindParametersToShader(std::vector<HrRenderEffectParameter*>& vecParameter
			, std::vector<HrRenderEffectStructParameter*>& vecRenderEffectStruct
			, std::vector<HrRenderEffectConstantBuffer*>& vecConstantBuffer
			, std::vector<HrShader*>& vecShader) override;
	private:
		void GetShaderMacros(std::vector<D3D_SHADER_MACRO>& defines, HrShader::EnumShaderType shaderType);

		HrRenderEffectConstantBuffer* GetConstantBuffer(std::vector<HrRenderEffectConstantBuffer*>& renderEffectConstBuffer, size_t nHashName);
		HrRenderEffectStructParameter* GetEffectStruct(std::vector<HrRenderEffectStructParameter*>& renderEffectStruct, size_t nHashName);
		HrRenderEffectParameter* GetEffectParameter(std::vector<HrRenderEffectParameter*>& renderEffectParameter, size_t nHashName);
		HrRenderParamDefine* GetRenderParamDefine(const std::string& strParamName);

	protected:
		UINT m_nConstantBufferSize = 0;
		UINT m_nConstantBufferNum = 0;
		UINT m_nNumSlots = 0;

		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_vecD3D11ShaderInputParameters;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_vecD3D11ShaderOutputParamters;

		std::unordered_map<size_t, D3D11ShaderDesc> m_mapShaderDesc;
		//std::array < D3D11ShaderDesc, HrShader::ST_NUMSHADERTYPES> m_arrShaderDesc;
	};
}

#endif

