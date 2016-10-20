#include "HrD3D11Mapping.h"

using namespace Hr;

LPCSTR HrD3D11Mapping::GetInputElementSemanticName(EnumVertexElementUsage usage)
{
	switch (usage)
	{
	case VEU_POSITION:
		return "POSITION";
	case VEU_NORMAL:
		return "NORMAL";
	case VEU_COLOR:
		return "COLOR";
	case VEU_DIFFUSE:
		return "COLOR"; // NB index will differentiat
	case VEU_SPECULAR:
		return "COLOR"; // NB index will differentiate
	case VEU_BLENDWEIGHT:
		return "BLENDWEIGHT";
	case VEU_BLENDINDEX:
		return "BLENDINDICES";
	case VEU_TEXTURECOORD:
		return "TEXCOORD";
	case VEU_TANGENT:
		return "TANGENT";
	case VEU_BINORMAL:
		return "BINORMAL";
	default:
		break;
	}
	return "";
}

DXGI_FORMAT HrD3D11Mapping::GetInputElementFormat(EnumVertexElementType type)
{
	switch (type)
	{
	case VET_COLOUR:
	case VET_COLOUR_ABGR:
	case VET_COLOUR_ARGB:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case VET_FLOAT1:
		return DXGI_FORMAT_R32_FLOAT;
	case VET_FLOAT2:
		return DXGI_FORMAT_R32G32_FLOAT;
	case VET_FLOAT3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case VET_FLOAT4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case VET_SHORT2:
		return DXGI_FORMAT_R16G16_SINT;
	case VET_SHORT4:
		return DXGI_FORMAT_R16G16B16A16_SINT;
	case VET_UBYTE4:
		return DXGI_FORMAT_R8G8B8A8_UINT;
	}
	// to keep compiler happy
	return DXGI_FORMAT_R32G32B32_FLOAT;
}

D3D_PRIMITIVE_TOPOLOGY HrD3D11Mapping::GetTopologyType(EnumTopologyType topologyType)
{
	switch (topologyType)
	{
	case TT_LINELIST:
		return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case TT_LINETRIP:
		return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case TT_POINTLIST:
		return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case TT_TRIANGLELIST:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case TT_TRIANGLETRIP:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	}
	return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

HrRenderParameter::EnumRenderParamType HrD3D11Mapping::GetRenderParamType(const std::string& strName)
{
	if ("worldviewproj_matrix" == strName)
	{
		return HrRenderParameter::RPT_WORLDVIEWPROJ_MATRIX;
	}
}

HrRenderParameter::EnumRenderParamDataType HrD3D11Mapping::GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType)
{
	switch (shaderVariableType)
	{
	case D3D_SVT_FLOAT:
		return HrRenderParameter::RPDT_FLOAT;
	default:
		break;
	}
}

DXGI_FORMAT HrD3D11Mapping::GetIndexBufferFormat(EnumIndexType indexType)
{
	switch (indexType)
	{
	case IT_16BIT:
		return DXGI_FORMAT_R16_UINT;
	case IT_32BIT:
		return DXGI_FORMAT_R32_UINT;
	default:
		break;
	}
}




