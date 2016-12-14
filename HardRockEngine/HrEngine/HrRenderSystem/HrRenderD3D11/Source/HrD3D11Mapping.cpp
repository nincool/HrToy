#include "HrD3D11Mapping.h"
#include <boost/assert.hpp>

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
	//case VEU_DIFFUSE:
		//return "COLOR"; // NB index will differentiat
	//case VEU_SPECULAR:
		//return "COLOR"; // NB index will differentiate
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

//EnumRenderParamType HrD3D11Mapping::GetRenderParamType(const std::string& strName)
//{
//	if ("world_view_proj_matrix" == strName)
//	{
//		return RPT_WORLDVIEWPROJ_MATRIX;
//	}
//}
//
EnumRenderEffectDataType HrD3D11Mapping::GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType)
{
	switch (shaderVariableType)
	{
	case D3D_SVT_FLOAT:
		return REDT_FLOAT1;
	default:
		break;
	}
}

uint32 HrD3D11Mapping::GetRenderParamDataSize(EnumRenderEffectDataType shaderVariableType)
{
	switch (shaderVariableType)
	{
	case REDT_FLOAT1:
		return 4;
	case REDT_FLOAT2:
		break;
	case REDT_FLOAT3:
		break;
	case REDT_FLOAT4:
		break;
	case REDT_SAMPLER1D:
		break;
	case REDT_SAMPLER2D:
		break;
	case REDT_SAMPLER3D:
		break;
	case REDT_SAMPLERCUBE:
		break;
	case REDT_SAMPLERRECT:
		break;
	case REDT_SAMPLER1DSHADOW:
		break;
	case REDT_SAMPLER2DSHADOW:
		break;
	case REDT_SAMPLER2DARRAY:
		break;
	case REDT_MATRIX_2X2:
		break;
	case REDT_MATRIX_2X3:
		break;
	case REDT_MATRIX_2X4:
		break;
	case REDT_MATRIX_3X2:
		break;
	case REDT_MATRIX_3X3:
		break;
	case REDT_MATRIX_3X4:
		break;
	case REDT_MATRIX_4X2:
		break;
	case REDT_MATRIX_4X3:
		break;
	case REDT_MATRIX_4X4:
		break;
	case REDT_INT1:
		break;
	case REDT_INT2:
		break;
	case REDT_INT3:
		break;
	case REDT_INT4:
		break;
	case REDT_SUBROUTINE:
		break;
	case REDT_DOUBLE1:
		break;
	case REDT_DOUBLE2:
		break;
	case REDT_DOUBLE3:
		break;
	case REDT_DOUBLE4:
		break;
	case REDT_MATRIX_DOUBLE_2X2:
		break;
	case REDT_MATRIX_DOUBLE_2X3:
		break;
	case REDT_MATRIX_DOUBLE_2X4:
		break;
	case REDT_MATRIX_DOUBLE_3X2:
		break;
	case REDT_MATRIX_DOUBLE_3X3:
		break;
	case REDT_MATRIX_DOUBLE_3X4:
		break;
	case REDT_MATRIX_DOUBLE_4X2:
		break;
	case REDT_MATRIX_DOUBLE_4X3:
		break;
	case REDT_MATRIX_DOUBLE_4X4:
		break;
	case REDT_UINT1:
		break;
	case REDT_UINT2:
		break;
	case REDT_UINT3:
		break;
	case REDT_UINT4:
		break;
	case REDT_BOOL1:
		break;
	case REDT_BOOL2:
		break;
	case REDT_BOOL3:
		break;
	case REDT_BOOL4:
		break;
	case REDT_SAMPLER_WRAPPER1D:
		break;
	case REDT_SAMPLER_WRAPPER2D:
		break;
	case REDT_SAMPLER_WRAPPER3D:
		break;
	case REDT_SAMPLER_WRAPPERCUBE:
		break;
	case REDT_SAMPLER_STATE:
		break;
	case REDT_UNKNOWN:
		break;
	default:
		break;
	}

	return 0;
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

D3D11_USAGE HrD3D11Mapping::GetGraphicsUsage(HrGraphicsBuffer::EnumGraphicsBufferUsage usage)
{
	switch (usage)
	{
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE:
		return D3D11_USAGE_DEFAULT;
	case HrGraphicsBuffer::HBU_GPUREAD_CPUWRITE:
		return D3D11_USAGE_DYNAMIC;
	case HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE:
		return D3D11_USAGE_IMMUTABLE;
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE:
		return D3D11_USAGE_STAGING;
		break;
	default:
		BOOST_ASSERT(nullptr);
	}
	return D3D11_USAGE_DEFAULT;
}

UINT HrD3D11Mapping::GetCPUAccessFlag(HrGraphicsBuffer::EnumGraphicsBufferUsage usage)
{
	switch (usage)
	{
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE:
		return 0;
	case HrGraphicsBuffer::HBU_GPUREAD_CPUWRITE:
		return D3D11_CPU_ACCESS_WRITE;
	case HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE:
		return 0;
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE:
		return (D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ);
	default:
		return 0;
	}

}

D3D11_BIND_FLAG HrD3D11Mapping::GetGraphicsBindFlag(HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag)
{
	switch (bindFlag)
	{
	case HrGraphicsBuffer::HBB_VERTEXT:
		return D3D11_BIND_VERTEX_BUFFER;
	case HrGraphicsBuffer::HBB_INDEX:
		return D3D11_BIND_INDEX_BUFFER;
	case HrGraphicsBuffer::HBB_CONST:
		return D3D11_BIND_CONSTANT_BUFFER;
	case HrGraphicsBuffer::HBB_SHADER_RESOURCE:
		return D3D11_BIND_SHADER_RESOURCE;
	default:
		BOOST_ASSERT(nullptr);
	}
	return D3D11_BIND_VERTEX_BUFFER;
}

D3D11_MAP HrD3D11Mapping::GetBufferMap(HrGraphicsBuffer::EnumGraphicsBufferUsage usage, HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag)
{
	D3D11_USAGE d3d11BufferUsage = GetGraphicsUsage(usage);
	BOOST_ASSERT(d3d11BufferUsage != D3D11_USAGE_DEFAULT && d3d11BufferUsage != D3D11_USAGE_IMMUTABLE);
	UINT d3dCPUAccessFlag = GetCPUAccessFlag(usage);
	BOOST_ASSERT(d3dCPUAccessFlag > 0);

	switch (accessFlag)
	{
	case HrGraphicsBuffer::HBA_READ_ONLY:
		BOOST_ASSERT(d3dCPUAccessFlag & D3D11_CPU_ACCESS_READ);
		return D3D11_MAP_READ;
	case HrGraphicsBuffer::HBA_WRITE_ONLY:
		BOOST_ASSERT(d3dCPUAccessFlag & D3D11_CPU_ACCESS_WRITE);
		if (d3d11BufferUsage == D3D11_USAGE_DYNAMIC)
		{
			return D3D11_MAP_WRITE_DISCARD;
		}
		else
		{
			return D3D11_MAP_WRITE;
		}
	case HrGraphicsBuffer::HBA_READ_WRITE:
		BOOST_ASSERT(d3dCPUAccessFlag & D3D11_CPU_ACCESS_READ && d3dCPUAccessFlag & D3D11_CPU_ACCESS_WRITE);
		return D3D11_MAP_READ_WRITE;
	case HrGraphicsBuffer::HBA_WRITE_NO_OVEWRITE:
		BOOST_ASSERT(d3dCPUAccessFlag & D3D11_CPU_ACCESS_WRITE);
		return D3D11_MAP_WRITE_NO_OVERWRITE; // This flag is only valid on vertex and index buffers
	default:
		BOOST_ASSERT(nullptr);
		return D3D11_MAP_READ;
	}
}

DXGI_FORMAT HrD3D11Mapping::GetPixelFormat(EnumPixelFormat pixelType)
{
	switch (pixelType)
	{
	case PF_L8:             return DXGI_FORMAT_R8_UNORM;
	case PF_L16:            return DXGI_FORMAT_R16_UNORM;
	case PF_A8:             return DXGI_FORMAT_A8_UNORM;
	case PF_A4L4:           return DXGI_FORMAT_UNKNOWN;
	case PF_BYTE_LA:        return DXGI_FORMAT_UNKNOWN;
	case PF_R3G3B2:         return DXGI_FORMAT_UNKNOWN;
	case PF_A1R5G5B5:       return DXGI_FORMAT_UNKNOWN;
	case PF_R5G6B5:         return DXGI_FORMAT_UNKNOWN;
	case PF_A4R4G4B4:       return DXGI_FORMAT_UNKNOWN;
	case PF_R8G8B8:         return DXGI_FORMAT_UNKNOWN;
	case PF_A8R8G8B8:       return DXGI_FORMAT_B8G8R8A8_UNORM;
	case PF_A8B8G8R8:       return DXGI_FORMAT_R8G8B8A8_UNORM;
	case PF_X8R8G8B8:       return DXGI_FORMAT_B8G8R8X8_UNORM;
	case PF_X8B8G8R8:       return DXGI_FORMAT_UNKNOWN;
	case PF_A2B10G10R10:    return DXGI_FORMAT_R10G10B10A2_TYPELESS;
	case PF_A2R10G10B10:    return DXGI_FORMAT_UNKNOWN;
	case PF_FLOAT16_R:      return DXGI_FORMAT_R16_FLOAT;
	case PF_FLOAT16_GR:     return DXGI_FORMAT_R16G16_FLOAT;
	case PF_FLOAT16_RGBA:   return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case PF_FLOAT32_R:      return DXGI_FORMAT_R32_FLOAT;
	case PF_FLOAT32_RGBA:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case PF_SHORT_RGBA:     return DXGI_FORMAT_R16G16B16A16_UNORM;
	case PF_DXT1:           return DXGI_FORMAT_BC1_UNORM;
	case PF_DXT2:           return DXGI_FORMAT_BC1_UNORM;
	case PF_DXT3:           return DXGI_FORMAT_BC2_UNORM;
	case PF_DXT4:           return DXGI_FORMAT_BC2_UNORM;
	case PF_DXT5:           return DXGI_FORMAT_BC3_UNORM;
	case PF_BC4_SNORM:      return DXGI_FORMAT_BC4_SNORM;
	case PF_BC4_UNORM:      return DXGI_FORMAT_BC4_UNORM;
	case PF_BC5_SNORM:      return DXGI_FORMAT_BC5_SNORM;
	case PF_BC5_UNORM:      return DXGI_FORMAT_BC5_UNORM;
	case PF_BC6H_UF16:      return DXGI_FORMAT_BC6H_UF16;
	case PF_BC6H_SF16:      return DXGI_FORMAT_BC6H_SF16;
	case PF_BC7_UNORM:      return DXGI_FORMAT_BC7_UNORM;
	case PF_BC7_UNORM_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;
	case PF_R16G16_SINT:    return DXGI_FORMAT_R16G16_SINT;
	case PF_FLOAT32_GR:     return DXGI_FORMAT_R32G32_FLOAT;
	case PF_UNKNOWN:
	default:                return DXGI_FORMAT_UNKNOWN;
	}

}

