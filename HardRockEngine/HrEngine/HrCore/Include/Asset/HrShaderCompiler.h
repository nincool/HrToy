#ifndef _HR_SHADERCOMPILER_H_
#define _HR_SHADERCOMPILER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrShaderCompiler
	{
	public:
		HrShaderCompiler();
		virtual ~HrShaderCompiler();

		virtual void CompileShaderFromCode();
	};
}

#endif