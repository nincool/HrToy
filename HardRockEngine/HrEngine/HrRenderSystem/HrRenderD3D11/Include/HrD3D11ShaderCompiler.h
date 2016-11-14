#ifndef _HR_D3D11SHADERCOMPILER_H_
#define _HR_D3D11SHADERCOMPILER_H_

#include "HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrRenderD3D11/Include/HrD3D11Shader.h"
#include <d3dcompiler.h>

namespace Hr
{
	struct D3D11ShaderParameterHandle
	{
		uint32_t shader_type;

		D3D_SHADER_VARIABLE_TYPE param_type;

		uint32_t cbuff;

		uint32_t offset;
		uint32_t elements;
		uint8_t rows;
		uint8_t columns;
	};

	struct D3D11ShaderDesc
	{
		D3D11ShaderDesc()
			: num_samplers(0), num_srvs(0), num_uavs(0)
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
				uint32 start_offset;
				uint32 type;
				uint32 rows;
				uint32 columns;
				uint32 elements;
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
			uint8_t type;
			uint8_t dimension;
			uint16_t bind_point;
		};
		std::vector<BoundResourceDesc> res_desc;
	};


	class HrD3D11ShaderCompiler 
	{
	public:
		HrD3D11ShaderCompiler();
		~HrD3D11ShaderCompiler();

		bool CompileShaderFromCode(HrStreamData& streamData
			, HrD3D11Shader::EnumShaderType shaderType
			, std::string& strEntryPoint
			, HrStreamData* pShaderBuffer);

		D3D11ShaderDesc& GetShaderDesc() { return m_shaderDesc; }
	protected:
		UINT m_nConstantBufferSize = 0;
		UINT m_nConstantBufferNum = 0;
		UINT m_nNumSlots = 0;

		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_vecD3D11ShaderInputParameters;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_vecD3D11ShaderOutputParamters;

		D3D11ShaderDesc m_shaderDesc;

	};
}

#endif