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

		virtual void CreateEffectParameters(std::unordered_map<size_t, HrRenderEffectParameterPtr>& mapParameters
			, std::unordered_map<size_t, HrRenderEffectConstantBufferPtr>& mapConstantBuffer) = 0;

		virtual void BindParametersToShader(std::unordered_map<size_t, HrRenderEffectParameterPtr>& mapRenderEffectParameters
			, std::unordered_map<size_t, HrRenderEffectConstantBufferPtr>& mapRenderConstantBuffers
			, std::unordered_map<std::string, HrShaderPtr>& mapShader) = 0;

		virtual HrStreamDataPtr GetCompiledData(const std::string& strEntryPoint) = 0;

	protected:
		std::string m_strFileName;

		HrStreamDataPtr m_pStreamData;
	};
}

#endif


