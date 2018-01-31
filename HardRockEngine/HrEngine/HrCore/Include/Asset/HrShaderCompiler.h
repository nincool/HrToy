#ifndef _HR_SHADERCOMPILER_H_
#define _HR_SHADERCOMPILER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrShader.h"

namespace Hr
{
	class HR_CORE_API HrShaderCompiler : public boost::noncopyable
	{
	public:
		HrShaderCompiler(const std::string& strFileName);
		virtual ~HrShaderCompiler();

		virtual bool CompileShaderFromCode(const std::string& strEntryPoint, HrShader::EnumShaderType shaderType) = 0;

		virtual bool ReflectEffectParameters(const std::string& strEntryPoint) = 0;

		virtual HrStreamDataPtr StripCompiledCode(const HrStreamData& shaderBuffer) = 0;

		virtual void CreateEffectParameters(std::vector<HrRenderEffectParameterPtr>& vecParameter
			, std::vector<HrRenderEffectStructParameterPtr>& vecRenderEffectStruct
			, std::vector<HrRenderEffectConstantBufferPtr>& vecConstantBuffer) = 0;

		virtual void BindParametersToShader(std::vector<HrRenderEffectParameterPtr>& vecParameter
			, std::vector<HrRenderEffectStructParameterPtr>& vecRenderEffectStruct
			, std::vector<HrRenderEffectConstantBufferPtr>& vecConstantBuffer
			, std::unordered_map<std::string, HrShaderPtr>& vecShader) = 0;

		virtual HrStreamDataPtr GetCompiledData(const std::string& strEntryPoint) = 0;

	protected:
		std::string m_strFileName;

		HrStreamDataPtr m_pStreamData;
	};
}

#endif


