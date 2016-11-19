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
		~HrShaderCompiler();

		virtual bool CompileShaderFromCode(std::string& strShaderFileName, HrStreamData& streamData
			, HrShader::EnumShaderType shaderType
			, std::string& strEntryPoint
			, HrStreamData& shaderBuffer) = 0;
	};
}

#endif


