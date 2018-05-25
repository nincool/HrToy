#include "HrD3D11ShaderCompiler.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <D3DCompiler.h>
#include <algorithm>


using namespace Hr;

HrD3D11ShaderCompiler::HrD3D11ShaderCompiler(const std::string& strFileName) 
	: HrShaderCompiler(strFileName)
{
}

HrD3D11ShaderCompiler::~HrD3D11ShaderCompiler()
{

}

bool HrD3D11ShaderCompiler::CompileShaderFromCode(const std::string& strEntryPoint, HrShader::EnumShaderType shaderType)
{
	auto itCompileData = m_mapCompileData.find(strEntryPoint);
	if (itCompileData != m_mapCompileData.end())
	{
		HRLOG("HrD3D11ShaderCompiler::CompileShaderFromCode the [%s] is be compiled!", strEntryPoint.c_str());
		return true;
	}

	HrD3D11IncludeShaderHandler includeHandler(m_strFileName);

	Byte* pSource = m_pStreamData->GetBufferPoint();
	uint64 nSize = m_pStreamData->GetBufferSize();

	std::vector<D3D_SHADER_MACRO> vecDefines;
	const D3D_SHADER_MACRO* pDefines = nullptr;
	GetShaderMacros(vecDefines, shaderType);
	pDefines = &vecDefines[0];

	UINT compileFlags = 0;
	//https://msdn.microsoft.com/en-us/library/windows/desktop/gg615083(v=vs.85).aspx
	//compileFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
	//Directs the compiler to pack matrices in column-major order on input and output from the shader. 
	//This type of packing is generally more efficient because a series of dot-products can then perform vector-matrix multiplication.
	//compileFlags |= D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR; 

	compileFlags |= D3DCOMPILE_ENABLE_STRICTNESS;
	compileFlags |= D3DCOMPILE_DEBUG;
	compileFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
	
	std::string strShaderModel = "";
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		strShaderModel = "vs_5_0";
		break;
	case HrShader::ST_PIXEL_SHADER:
		strShaderModel = "ps_5_0";
		break;
	default:
		break;
	}

	ID3DBlob* pD3DShaderBuffer = nullptr;
	ID3DBlob* pErrorBuffer = nullptr;

	std::wstring strWFileName(m_strFileName.length(), L' ');
	std::copy(m_strFileName.begin(), m_strFileName.end(), strWFileName.begin());
	HRESULT hr = D3DCompileFromFile(
		strWFileName.c_str(),
		pDefines,
		&includeHandler,
		strEntryPoint.c_str(),
		strShaderModel.c_str(),
		compileFlags,
		NULL,
		&pD3DShaderBuffer,
		&pErrorBuffer
	);

	/*
	HRESULT hr = D3DCompile(
		pSource,					// [in] Pointer to the shader in memory. 
		nSize,						// [in] Size of the shader in memory.  
		m_strFileName.c_str(),      // [in] Optional. You can use this parameter for strings that specify error messages.
		pDefines,					// [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL. 
		&includeHandler,			// [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
		strEntryPoint.c_str(),		// [in] Name of the shader-entrypoint function where shader execution begins. 
		strShaderModel.c_str(),		// [in] A string that specifies the shader model; can be any profile in shader model 4 or higher. 
		compileFlags,				// [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
		NULL,						// [in] Effect compile flags
		&pD3DShaderBuffer,			// [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
		&pErrorBuffer				// [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
	);
	*/

	if (FAILED(hr))
	{
		if (pErrorBuffer != 0)
		{
			char* pMsg = (char*)(pErrorBuffer->GetBufferPointer());
			HRERROR(pMsg);
			pErrorBuffer->Release();
		}
		BOOST_ASSERT(nullptr);
		return false;
	}

	if (pErrorBuffer != 0)
		pErrorBuffer->Release();


	HrStreamDataPtr pCompiledData = HrMakeSharedPtr<HrStreamData>();
	pCompiledData->ResizeBuffer(pD3DShaderBuffer->GetBufferSize());
	memcpy(pCompiledData->GetBufferPoint(), pD3DShaderBuffer->GetBufferPointer(), pD3DShaderBuffer->GetBufferSize());

#if (HR_DEBUG > 0)
	m_mapCompileData.insert(std::make_pair(strEntryPoint, std::make_tuple(shaderType, pCompiledData, nullptr, D3D11ShaderDesc())));
#else
	auto pStripStreamData = StripCompiledCode(*pCompiledData.get());
	m_mapCompileData.insert(std::make_pair(strEntryPoint, std::make_tuple(shaderType, pCompiledData, pStripStreamData, D3D11ShaderDesc())));
#endif
	
	

	pD3DShaderBuffer->Release();

	ReflectEffectParameters(strEntryPoint);
}

void HrD3D11ShaderCompiler::GetShaderMacros(std::vector<D3D_SHADER_MACRO>& defines, HrShader::EnumShaderType shaderType)
{
	//Add D3D11 define to all program, compiled with D3D11 RenderSystem
	D3D_SHADER_MACRO macro = { "D3D11","1" };
	defines.push_back(macro);

	// Using different texture sampling instructions, tex2D for D3D9 and SampleXxx for D3D11,
	// declaring type of BLENDINDICES as float4 for D3D9 but as uint4 for D3D11 -  all those
	// small but annoying differences that otherwise would require declaring separate programs.
	macro.Name = "SHADER_MODEL_5";
	defines.push_back(macro);

	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		macro.Name = "HR_VERTEX_SAHDER";
		break;
	case HrShader::ST_PIXEL_SHADER:
		macro.Name = "HR_PIXEL_SHADER";
		break;
	case HrShader::ST_GEOMETRY_SHADER:
		macro.Name = "HR_GEOMETRY_SHADER";
		break;
	case HrShader::ST_DOMAIN_SHADER:
		macro.Name = "HR_DOMAIN_SHADER";
		break;
	case HrShader::ST_HULL_SHADER:
		macro.Name = "HR_HULL_SHADER";
		break;
	case HrShader::ST_COMPUTE_SHADER:
		macro.Name = "HR_COMPUTE_SHADER";
		break;
	default:
		BOOST_ASSERT(false);
		break;
	}
	defines.push_back(macro);

	// Add NULL terminator
	macro.Name = 0;
	macro.Definition = 0;
	defines.push_back(macro);

}

bool HrD3D11ShaderCompiler::ReflectEffectParameters(const std::string& strEntryPoint)
{
	auto iteCompileData = m_mapCompileData.find(strEntryPoint);
	if (iteCompileData == m_mapCompileData.end())
	{
		HRERROR("HrD3D11ShaderCompile::ReflectEffectParamters Error! EntryPoint[%s]", strEntryPoint.c_str());
		return false;
	}
	
	HrStreamDataPtr pStreamData = std::get<1>(iteCompileData->second);

	uint64 nBufferSize = pStreamData->GetBufferSize();
	ID3D11ShaderReflection* pShaderReflection = nullptr;
	TIF(D3DReflect((void*)pStreamData->GetBufferPoint()
		, nBufferSize
		, IID_ID3D11ShaderReflection
		, (void**)&pShaderReflection));
	
	D3D11_SHADER_DESC shaderDesc;
	TIF(pShaderReflection->GetDesc(&shaderDesc));

	auto& desc = std::get<3>(iteCompileData->second);

	for (uint32 nCBIndex = 0; nCBIndex < shaderDesc.ConstantBuffers; ++nCBIndex)
	{
		ID3D11ShaderReflectionConstantBuffer* pShaderReflectionConstantBuffer = pShaderReflection->GetConstantBufferByIndex(nCBIndex);;

		D3D11_SHADER_BUFFER_DESC constantBufferDesc;
		TIF(pShaderReflectionConstantBuffer->GetDesc(&constantBufferDesc));

		D3D_CBUFFER_TYPE bufferType = constantBufferDesc.Type;

		switch (bufferType)
		{
		case D3D_CT_CBUFFER:
		case D3D_CT_TBUFFER:
		{
			D3D11ShaderDesc::ConstantBufferDesc cbDesc;
			cbDesc.name = constantBufferDesc.Name;
			cbDesc.name_hash = HrHashValue(cbDesc.name);
			cbDesc.size = constantBufferDesc.Size;

			for (uint32 nCBVarIndex = 0; nCBVarIndex < constantBufferDesc.Variables; ++nCBVarIndex)
			{
				ID3D11ShaderReflectionVariable* pVarRef = pShaderReflectionConstantBuffer->GetVariableByIndex(nCBVarIndex);

				D3D11_SHADER_VARIABLE_DESC constVarDesc;
				TIF(pVarRef->GetDesc(&constVarDesc));

				ID3D11ShaderReflectionType* pVarRefType = pVarRef->GetType();
				D3D11_SHADER_TYPE_DESC varRefTypeDesc;
				TIF(pVarRefType->GetDesc(&varRefTypeDesc));

				D3D11ShaderDesc::ConstantBufferDesc::VariableDesc constantVariableDesc;
				constantVariableDesc.name = constVarDesc.Name;
				constantVariableDesc.start_offset = constVarDesc.StartOffset;
				constantVariableDesc.size = static_cast<uint32>(constVarDesc.Size);

				constantVariableDesc.typeName = varRefTypeDesc.Name;
				constantVariableDesc.varClass = static_cast<uint32>(varRefTypeDesc.Class);
				constantVariableDesc.type = static_cast<uint8>(varRefTypeDesc.Type);//D3D_SHADER_VARIABLE_TYPE https://msdn.microsoft.com/en-us/library/windows/desktop/ff728735(v=vs.85).aspx
				constantVariableDesc.rows = static_cast<uint8>(varRefTypeDesc.Rows);
				constantVariableDesc.columns = static_cast<uint8>(varRefTypeDesc.Columns);
				constantVariableDesc.elements = static_cast<uint16>(varRefTypeDesc.Elements);
				constantVariableDesc.elements = constantVariableDesc.elements > 0 ? constantVariableDesc.elements : 1;
				constantVariableDesc.bUsed = constVarDesc.uFlags & D3D_SVF_USED;
				constantVariableDesc.name_hash = HrHashValue(constantVariableDesc.name);
		
				//struct
				if (constantVariableDesc.varClass == D3D_SVC_STRUCT)
				{
					for (uint32 nStructVarIndex = 0; nStructVarIndex < varRefTypeDesc.Members; ++nStructVarIndex)
					{
						D3D11_SHADER_TYPE_DESC memberTypeDesc;
						ID3D11ShaderReflectionType* pMemberType = pVarRefType->GetMemberTypeByIndex(nStructVarIndex);

						pMemberType->GetDesc(&memberTypeDesc);
						D3D11ShaderDesc::ConstantBufferDesc::VariableDesc structVariableDesc;
						structVariableDesc.name = pVarRefType->GetMemberTypeName(nStructVarIndex);
						structVariableDesc.start_offset = memberTypeDesc.Offset;

						structVariableDesc.varClass = static_cast<uint32>(memberTypeDesc.Class);
						structVariableDesc.type = static_cast<uint8>(memberTypeDesc.Type);
						structVariableDesc.rows = static_cast<uint8>(memberTypeDesc.Rows);
						structVariableDesc.columns = static_cast<uint8>(memberTypeDesc.Columns);
						structVariableDesc.elements = static_cast<uint16>(memberTypeDesc.Elements);
						structVariableDesc.elements = structVariableDesc.elements > 0 ? structVariableDesc.elements : 1;
						structVariableDesc.bUsed = constantVariableDesc.bUsed;
						constantVariableDesc.struct_desc.push_back(structVariableDesc);
					}

					if (constantVariableDesc.struct_desc.size() == 1)
					{
						constantVariableDesc.struct_desc[0].size = constantVariableDesc.size;
					}
					else
					{
						if (constantVariableDesc.struct_desc.size() >= 2)
						{
							uint32 nLastVariableOffset = 0;
							for (size_t nStructVariableIndex = 0; nStructVariableIndex < constantVariableDesc.struct_desc.size() - 1; ++nStructVariableIndex)
							{
								constantVariableDesc.struct_desc[nStructVariableIndex].size =
									constantVariableDesc.struct_desc[nStructVariableIndex + 1].start_offset - constantVariableDesc.struct_desc[nStructVariableIndex].start_offset;
							}
							constantVariableDesc.struct_desc[constantVariableDesc.struct_desc.size() - 1].size =
								constantVariableDesc.size - constantVariableDesc.struct_desc[constantVariableDesc.struct_desc.size() - 1].start_offset
								+ constantVariableDesc.start_offset;
						}
					}
				}

				cbDesc.var_desc.push_back(constantVariableDesc);

			}
			desc.cb_desc.push_back(cbDesc);

			break;
		}
		default:
			break;
		}
	}

	int nSamplers = -1;
	int nSrvs = -1;
	int nUavs = -1;
	for (uint32 i = 0; i < shaderDesc.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC shaderInputDesc;
		pShaderReflection->GetResourceBindingDesc(i, &shaderInputDesc);

		switch (shaderInputDesc.Type)
		{
		case D3D_SIT_SAMPLER:
		{
			nSamplers = (std::max)(nSamplers, static_cast<int>(shaderInputDesc.BindPoint));
			D3D11ShaderDesc::BoundResourceDesc bindResourceDesc;
			bindResourceDesc.name = shaderInputDesc.Name;
			bindResourceDesc.name_hash = HrHashValue(bindResourceDesc.name);
			bindResourceDesc.type = static_cast<uint8>(shaderInputDesc.Type);
			bindResourceDesc.bind_point = static_cast<uint16>(shaderInputDesc.BindPoint);
			bindResourceDesc.dimension = static_cast<uint8>(shaderInputDesc.Dimension);
			desc.res_desc.push_back(bindResourceDesc);
			break;
		}
		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		case D3D_SIT_BYTEADDRESS:
		{
			nSrvs = (std::max)(nSrvs, static_cast<int>(shaderInputDesc.BindPoint));
			D3D11ShaderDesc::BoundResourceDesc bindResourceDesc;
			bindResourceDesc.name = shaderInputDesc.Name;
			bindResourceDesc.name_hash = HrHashValue(bindResourceDesc.name);
			bindResourceDesc.type = static_cast<uint8>(shaderInputDesc.Type);
			bindResourceDesc.bind_point = static_cast<uint16>(shaderInputDesc.BindPoint);
			bindResourceDesc.dimension = static_cast<uint8>(shaderInputDesc.Dimension);
			desc.res_desc.push_back(bindResourceDesc);
			break;

		}
		case D3D_SIT_UAV_RWTYPED:
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_RWBYTEADDRESS:
		case D3D_SIT_UAV_APPEND_STRUCTURED:
		case D3D_SIT_UAV_CONSUME_STRUCTURED:
		case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
		{
			nUavs = (std::max)(nUavs, static_cast<int>(shaderInputDesc.BindPoint));
			D3D11ShaderDesc::BoundResourceDesc bindResourceDesc;
			bindResourceDesc.name = shaderInputDesc.Name;
			bindResourceDesc.name_hash = HrHashValue(bindResourceDesc.name);
			bindResourceDesc.type = static_cast<uint8>(shaderInputDesc.Type);
			bindResourceDesc.bind_point = static_cast<uint16>(shaderInputDesc.BindPoint);
			bindResourceDesc.dimension = static_cast<uint8>(shaderInputDesc.Dimension);
			desc.res_desc.push_back(bindResourceDesc);
			break;
		}
		}
	}
	desc.num_samplers = static_cast<uint16>(nSamplers + 1);
	desc.num_srvs = static_cast<uint16>(nSrvs + 1);
	desc.num_uavs = static_cast<uint16>(nUavs + 1);

	//get the input parameters
	desc.verInput_desc.resize(shaderDesc.InputParameters);
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC curParam;
		pShaderReflection->GetInputParameterDesc(i, &curParam);
		desc.verInput_desc[i].strSimantic = curParam.SemanticName;
		desc.verInput_desc[i].nSimanticIndex = curParam.SemanticIndex;
	}

	//get the output parameters
	desc.verOutput_desc.resize(shaderDesc.OutputParameters);
	for (UINT i = 0; i < shaderDesc.OutputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC curParam;
		pShaderReflection->GetOutputParameterDesc(i, &curParam);
		desc.verOutput_desc[i].strSimantic = curParam.SemanticName;
		desc.verOutput_desc[i].nSimanticIndex = curParam.SemanticIndex;
	}

	SAFE_RELEASE(pShaderReflection);

	return true;
}

HrStreamDataPtr HrD3D11ShaderCompiler::StripCompiledCode(const HrStreamData& shaderBuffer)
{
	ID3DBlob* pStrippedBlob = nullptr;
	HRESULT hr = D3DStripShader(shaderBuffer.GetBufferPoint(), shaderBuffer.GetBufferSize(), D3DCOMPILER_STRIP_REFLECTION_DATA | D3DCOMPILER_STRIP_DEBUG_INFO
		| D3DCOMPILER_STRIP_TEST_BLOBS | D3DCOMPILER_STRIP_PRIVATE_DATA, &pStrippedBlob);
	HrStreamDataPtr pStripStreamData = HrMakeSharedPtr<HrStreamData>();
	pStripStreamData->AddBuffer(static_cast<Byte*>(pStrippedBlob->GetBufferPointer()), pStrippedBlob->GetBufferSize());
	SAFE_RELEASE(pStrippedBlob);

	return pStripStreamData;
}

void HrD3D11ShaderCompiler::CreateEffectParameters(std::unordered_map<size_t, HrRenderEffectParameterPtr>& mapParameters, std::unordered_map<size_t, HrRenderEffectConstantBufferPtr>& mapConstantBuffer)
{
	for (auto shaderDescItem : m_mapCompileData)
	{
		D3D11ShaderDesc& shaderDesc = std::get<3>(shaderDescItem.second);
		//shader const desc
		uint32 nConstBuffer = shaderDesc.cb_desc.size();
		for (uint32 nCBIndex = 0; nCBIndex < nConstBuffer; ++nCBIndex)
		{
			D3D11ShaderDesc::ConstantBufferDesc& cbDesc = shaderDesc.cb_desc[nCBIndex];

			HrRenderEffectConstantBufferPtr pConstBuffer = nullptr;
			auto iteBuffer = mapConstantBuffer.find(cbDesc.name_hash);
			if (iteBuffer == mapConstantBuffer.end())
			{
				pConstBuffer = HrMakeSharedPtr<HrRenderEffectConstantBuffer>(cbDesc.name, cbDesc.name_hash, cbDesc.size);
				mapConstantBuffer[cbDesc.name_hash] = pConstBuffer;
			}
			else
			{
				continue;
			}

			uint32 nVarNum = shaderDesc.cb_desc[nCBIndex].var_desc.size();
			for (uint32 nVarIndex = 0; nVarIndex < nVarNum; ++nVarIndex)
			{
				D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& varDesc = shaderDesc.cb_desc[nCBIndex].var_desc[nVarIndex];
				if (varDesc.varClass == D3D_SVC_STRUCT)
				{
					for (size_t nEleIndex = 0; nEleIndex < varDesc.elements; ++nEleIndex)
					{
						for (uint32 nStructMemIndex = 0; nStructMemIndex < varDesc.struct_desc.size(); ++nStructMemIndex)
						{
							D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& varStructMen = varDesc.struct_desc[nStructMemIndex];
							varStructMen.name_hash = varDesc.name_hash;
							HrHashCombine(varStructMen.name_hash, nEleIndex);
							HrHashCombine(varStructMen.name_hash, varStructMen.name);
							HrRenderEffectParameterPtr pEffectParameter = HrMakeSharedPtr<HrRenderEffectParameter>(varStructMen.name, varStructMen.name_hash);

							const HrRenderParamDefine* pRenderParamDefine = GetRenderParamDefine(varStructMen.name);
							if (pRenderParamDefine != nullptr)
							{
								pEffectParameter->ParamInfo(pRenderParamDefine->paramType
									, pRenderParamDefine->dataType
									, HrRenderEffectParameter::REPBT_CONSTBUFFER
									, varStructMen.size / varStructMen.elements
									, varStructMen.elements);

								pEffectParameter->BindConstantBuffer(pConstBuffer, varStructMen.start_offset + varDesc.start_offset + varDesc.size * nEleIndex);
							}
							else
							{
								//todo 自定义变量
								EnumRenderEffectDataType redt = HrD3D11Mapping::GetRenderParamDataType((D3D_SHADER_VARIABLE_TYPE)varDesc.type, varDesc.rows, varDesc.columns);
								pEffectParameter->ParamInfo(PRT_CUSTOM
									, redt
									, HrRenderEffectParameter::REPBT_CONSTBUFFER
									, HrD3D11Mapping::GetRenderParamDataSize(redt)
									, varStructMen.elements);
								pEffectParameter->BindConstantBuffer(pConstBuffer, varStructMen.start_offset + varDesc.start_offset + varDesc.size * nEleIndex);
							}

							mapParameters[varStructMen.name_hash] = pEffectParameter;
							
						}
					}
				}
				else
				{
					//if it is worldviewprojmatrix , the class is D3D_SVC_MATRIX_COLUMNS, need to transpose the matrix
					HrRenderEffectParameterPtr pEffectParameter = HrMakeSharedPtr<HrRenderEffectParameter>(varDesc.name, varDesc.name_hash);
					const HrRenderParamDefine* pRenderParamDefine = GetRenderParamDefine(varDesc.name);
					if (pRenderParamDefine != nullptr)
					{
						pEffectParameter->ParamInfo(pRenderParamDefine->paramType
							, pRenderParamDefine->dataType
							, HrRenderEffectParameter::REPBT_CONSTBUFFER
							, pRenderParamDefine->nStride
							, varDesc.elements);
						pEffectParameter->BindConstantBuffer(pConstBuffer, varDesc.start_offset);
					}
					else
					{
						EnumRenderEffectDataType redt = HrD3D11Mapping::GetRenderParamDataType((D3D_SHADER_VARIABLE_TYPE)varDesc.type, varDesc.rows, varDesc.columns);
						pEffectParameter->ParamInfo(EnumRenderParamType::PRT_CUSTOM
							, redt
							, HrRenderEffectParameter::REPBT_CONSTBUFFER
							, HrD3D11Mapping::GetRenderParamDataSize(redt)
							, varDesc.elements);
						pEffectParameter->BindConstantBuffer(pConstBuffer, varDesc.start_offset);
					}

					mapParameters[varDesc.name_hash] = pEffectParameter;
				}
			}
		}

		// shader resource desc
		//uint32 nResBindCount = shaderDesc.res_desc.size();
		//for (uint32 nResIndex = 0; nResIndex < nResBindCount; ++nResIndex)
		//{
		//	D3D11ShaderDesc::BoundResourceDesc& bindResDesc = shaderDesc.res_desc[nResIndex];
		//	switch (bindResDesc.type)
		//	{
		//	case D3D_SIT_TEXTURE:
		//	{
		//		HrRenderEffectParameter* pEffectParameter = HR_NEW HrRenderEffectParameter(bindResDesc.name, bindResDesc.name_hash);
		//		pEffectParameter->ParamInfo(RPT_TEXTURE, REDT_TEXTURE2D, HrRenderEffectParameter::REPBT_RESOURCE, 0, 1);
		//		vecParameter.push_back(pEffectParameter);
		//		break;
		//	}
		//	case D3D_SIT_SAMPLER:
		//	{
		//		HrRenderEffectParameter* pEffectParameter = HR_NEW HrRenderEffectParameter(bindResDesc.name, bindResDesc.name_hash);
		//		pEffectParameter->ParamInfo(RPT_SAMPLER, REDT_SAMPLER2D, HrRenderEffectParameter::REPBT_RESOURCE, 0, 1);
		//		vecParameter.push_back(pEffectParameter);
		//		break;
		//	}
		//	}
		//}
	}
}

void HrD3D11ShaderCompiler::BindParametersToShader(std::unordered_map<size_t, HrRenderEffectParameterPtr>& mapRenderEffectParameters
	, std::unordered_map<size_t, HrRenderEffectConstantBufferPtr>& mapRenderConstantBuffers
	, std::unordered_map<std::string, HrShaderPtr>& mapShader)
{
	std::vector<HrRenderEffectConstantBufferPtr> vecShaderBindConstantBuffers;
	for (auto itemShader : mapShader)
	{
		for (auto itemDesc : m_mapCompileData)
		{
			if (itemShader.first == itemDesc.first)
			{
				const D3D11ShaderDesc& d3dDescShader = std::get<3>(itemDesc.second);
				for (size_t nCBIndex = 0; nCBIndex < d3dDescShader.cb_desc.size(); ++nCBIndex)
				{
					const D3D11ShaderDesc::ConstantBufferDesc& cbDesc = d3dDescShader.cb_desc[nCBIndex];
					auto iteConstantBuff = mapRenderConstantBuffers.find(cbDesc.name_hash);
					BOOST_ASSERT(iteConstantBuff != mapRenderConstantBuffers.end());
					vecShaderBindConstantBuffers.push_back(iteConstantBuff->second);
				}

				break;
			}
		}
		itemShader.second->BindRenderParameter(vecShaderBindConstantBuffers);
	}
}

HrStreamDataPtr HrD3D11ShaderCompiler::GetCompiledData(const std::string& strEntryPoint)
{
	auto iteCompiledInfo = m_mapCompileData.find(strEntryPoint);
	if (iteCompiledInfo != m_mapCompileData.end())
	{
		HrStreamDataPtr pCompiledData = std::get<1>(iteCompiledInfo->second);

		return pCompiledData;
	}

	return nullptr;
}

HrRenderEffectConstantBufferPtr HrD3D11ShaderCompiler::GetConstantBuffer(std::vector<HrRenderEffectConstantBufferPtr>& vecConstBuffer, size_t nHashName)
{
	for (uint32 nRECBIndex = 0; nRECBIndex < vecConstBuffer.size(); ++nRECBIndex)
	{
		if (vecConstBuffer[nRECBIndex]->HashName() == nHashName)
		{
			return vecConstBuffer[nRECBIndex];
		}
	}

	return nullptr;
}

HrRenderEffectParameterPtr HrD3D11ShaderCompiler::GetEffectParameter(std::vector<HrRenderEffectParameterPtr>& renderEffectParameter, size_t nHashName)
{
	for (uint32 nREPIndex = 0; nREPIndex < renderEffectParameter.size(); ++nREPIndex)
	{
		if (renderEffectParameter[nREPIndex]->HashName() == nHashName)
		{
			return renderEffectParameter[nREPIndex];
		}
	}

	return nullptr;
}

const HrRenderParamDefine* HrD3D11ShaderCompiler::GetRenderParamDefine(const std::string& strParamName)
{
	uint32 nDefineParamSize = HrRenderParamDefine::m_s_vecRenderParamDefine.size();
	for (uint32 i = 0; i < nDefineParamSize; ++i)
	{
		if (strParamName == HrRenderParamDefine::m_s_vecRenderParamDefine[i].strName)
		{
			return &HrRenderParamDefine::m_s_vecRenderParamDefine[i];
		}
	}

	return nullptr;
}

void HrD3D11ShaderCompiler::GetVertexInputOutputSimantic(std::string strVSEnterPoint
	, std::vector<std::pair<EnumVertexElementSemantic, uint32> >& vecInputSimaintic
	, std::vector<std::pair<EnumVertexElementSemantic, uint32> >& vecOutputSimantic)
{
	for (auto& itShaderData : m_mapCompileData)
	{
		if (itShaderData.first == strVSEnterPoint)
		{
			const D3D11ShaderDesc& desc = std::get<3>(itShaderData.second);
			vecInputSimaintic.reserve(desc.verInput_desc.size());
			for (size_t i = 0; i < desc.verInput_desc.size(); ++i)
			{
				vecInputSimaintic.push_back(std::make_pair(HrD3D11Mapping::GetInputElementSemanticName(desc.verInput_desc[i].strSimantic), desc.verInput_desc[i].nSimanticIndex));
			}
			vecOutputSimantic.reserve(desc.verInput_desc.size());
			for (size_t i = 0; i < desc.verOutput_desc.size(); ++i)
			{
				vecOutputSimantic.push_back(std::make_pair(HrD3D11Mapping::GetInputElementSemanticName(desc.verOutput_desc[i].strSimantic), desc.verOutput_desc[i].nSimanticIndex));
			}

			break;
		}
	}
}
