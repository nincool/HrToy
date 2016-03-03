#ifndef _HR_SHADERCOMPILER_H_
#define _HR_SHADERCOMPILER_H_

#include "HrCore/Include/Asset/IShaderCompiler.h"

namespace Hr
{
	class HR_CORE_API HrShaderCompiler : public IShaderCompiler
	{
	public:
		HrShaderCompiler();
		~HrShaderCompiler();

		virtual void CompileShaderFromCode() override;
	};
}

#endif