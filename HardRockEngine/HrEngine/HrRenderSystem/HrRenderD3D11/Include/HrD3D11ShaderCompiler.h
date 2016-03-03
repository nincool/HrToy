#ifndef _HR_D3D11SHADERCOMPILER_H_
#define _HR_D3D11SHADERCOMPILER_H_

#include "HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Asset/HrShaderCompiler.h"

namespace Hr
{
	class HrD3D11ShaderCompiler : public HrShaderCompiler
	{
	public:
		HrD3D11ShaderCompiler();
		~HrD3D11ShaderCompiler();
	};
}

#endif