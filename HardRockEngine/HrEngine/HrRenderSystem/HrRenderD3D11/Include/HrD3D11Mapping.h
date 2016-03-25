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
		//InputElement SemanticNameת��
		static LPCSTR GetInputElementSemanticName(EnumVertexElementUsage usage);

		static DXGI_FORMAT GetInputElementFormat(EnumVertexElementType type);
		//��������
		static D3D_PRIMITIVE_TOPOLOGY GetTopologyType(EnumTopologyType topologyType);
		//���������ʽ
		static DXGI_FORMAT GetIndexBufferFormat(EnumIndexType indexType);

		static HrRenderParameter::EnumRenderParamType GetRenderParamType(const std::string& strName);
		static HrRenderParameter::EnumRenderParamDataType GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType);
	};
}

#endif




