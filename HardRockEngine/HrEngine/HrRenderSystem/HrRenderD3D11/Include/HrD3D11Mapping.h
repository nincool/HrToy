#ifndef _HR_D3D11MAPPING_H_
#define _HR_D3D11MAPPING_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Render/HrRenderParameter.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11Mapping
	{
	public:
		//InputElement SemanticName×ª»¯
		static LPCSTR GetInputElementSemanticName(HrVertexElement::EnumVertexElementUsage usage);
		static DXGI_FORMAT GetInputElementFormat(HrVertexElement::EnumVertexElementType type);

		static HrRenderParameter::EnumRenderParamType GetRenderParamType(const std::string& strName);
		static HrRenderParameter::EnumRenderParamDataType GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType);
	};
}

#endif




