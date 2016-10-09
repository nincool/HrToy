#ifndef _I_SHADERCOMPILER_H_
#define _I_SHADERCOMPILER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API IShaderCompiler 
	{
	public:
		virtual ~IShaderCompiler(){}

		virtual void CompileShaderFromCode() = 0;
	};
}

#endif