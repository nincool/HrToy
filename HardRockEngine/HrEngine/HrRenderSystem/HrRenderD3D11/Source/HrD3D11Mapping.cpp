#include "HrD3D11Mapping.h"

using namespace Hr;

LPCSTR HrD3D11Mapping::GetInputElementSemanticName(HrVertexElement::EnumVertexElementUsage usage)
{
	switch (usage)
	{
	case Hr::HrVertexElement::VEU_POSITION:
		return "POSITION";
	case Hr::HrVertexElement::VEU_NORMAL:
		break;
	case Hr::HrVertexElement::VEU_DIFFUSE:
		break;
	case Hr::HrVertexElement::VEU_SPECULAR:
		break;
	case Hr::HrVertexElement::VEU_BLENDWEIGHT:
		break;
	case Hr::HrVertexElement::VEU_BLENDINDEX:
		break;
	case Hr::HrVertexElement::VEU_TEXTURECOORD:
		break;
	case Hr::HrVertexElement::VEU_TANGENT:
		break;
	case Hr::HrVertexElement::VEU_BINORMAL:
		break;
	default:
		break;
	}
	return "";
}

DXGI_FORMAT HrD3D11Mapping::GetInputElementFormat(HrVertexElement::EnumVertexElementType type)
{
	switch (type)
	{
	case HrVertexElement::VET_COLOUR:
	case HrVertexElement::VET_COLOUR_ABGR:
	case HrVertexElement::VET_COLOUR_ARGB:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case HrVertexElement::VET_FLOAT1:
		return DXGI_FORMAT_R32_FLOAT;
	case HrVertexElement::VET_FLOAT2:
		return DXGI_FORMAT_R32G32_FLOAT;
	case HrVertexElement::VET_FLOAT3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case HrVertexElement::VET_FLOAT4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case HrVertexElement::VET_SHORT2:
		return DXGI_FORMAT_R16G16_SINT;
	case HrVertexElement::VET_SHORT4:
		return DXGI_FORMAT_R16G16B16A16_SINT;
	case HrVertexElement::VET_UBYTE4:
		return DXGI_FORMAT_R8G8B8A8_UINT;
	}
	// to keep compiler happy
	return DXGI_FORMAT_R32G32B32_FLOAT;
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

