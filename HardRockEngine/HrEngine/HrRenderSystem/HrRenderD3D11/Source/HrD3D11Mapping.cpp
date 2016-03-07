#include "HrD3D11Mapping.h"

using namespace Hr;

LPCSTR HrD3D11Mapping::GetInputElementSemanticName(HrVertextElement::EnumVertextElementUsage usage)
{
	switch (usage)
	{
	case Hr::HrVertextElement::VEU_POSITION:
		return "POSITION";
	case Hr::HrVertextElement::VEU_NORMAL:
		break;
	case Hr::HrVertextElement::VEU_DIFFUSE:
		break;
	case Hr::HrVertextElement::VEU_SPECULAR:
		break;
	case Hr::HrVertextElement::VEU_BLENDWEIGHT:
		break;
	case Hr::HrVertextElement::VEU_BLENDINDEX:
		break;
	case Hr::HrVertextElement::VEU_TEXTURECOORD:
		break;
	case Hr::HrVertextElement::VEU_TANGENT:
		break;
	case Hr::HrVertextElement::VEU_BINORMAL:
		break;
	default:
		break;
	}
	return "";
}

DXGI_FORMAT HrD3D11Mapping::GetInputElementFormat(HrVertextElement::EnumVertexElementType type)
{
	switch (type)
	{
	case HrVertextElement::VET_COLOUR:
	case HrVertextElement::VET_COLOUR_ABGR:
	case HrVertextElement::VET_COLOUR_ARGB:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case HrVertextElement::VET_FLOAT1:
		return DXGI_FORMAT_R32_FLOAT;
	case HrVertextElement::VET_FLOAT2:
		return DXGI_FORMAT_R32G32_FLOAT;
	case HrVertextElement::VET_FLOAT3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case HrVertextElement::VET_FLOAT4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case HrVertextElement::VET_SHORT2:
		return DXGI_FORMAT_R16G16_SINT;
	case HrVertextElement::VET_SHORT4:
		return DXGI_FORMAT_R16G16B16A16_SINT;
	case HrVertextElement::VET_UBYTE4:
		return DXGI_FORMAT_R8G8B8A8_UINT;
	}
	// to keep compiler happy
	return DXGI_FORMAT_R32G32B32_FLOAT;
}

