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
	case VEU_TEXTURE_COORDINATES:
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

D3D11_INPUT_CLASSIFICATION HrD3D11Mapping::GetInputELementClassType(EnumVertexElementClassType type)
{
	switch (type)
	{
	case VEC_INSTANCE:
		return D3D11_INPUT_PER_INSTANCE_DATA;
	case VEC_GEOMETRY:
		return D3D11_INPUT_PER_VERTEX_DATA;
	default:
		break;
	}
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

EnumRenderEffectDataType HrD3D11Mapping::GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType)
{
	switch (shaderVariableType)
	{
	case D3D_SVT_FLOAT:
		return REDT_FLOAT1;
	case D3D_SVT_UINT:
		return REDT_UINT1;
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
		return 4;
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

DXGI_FORMAT HrD3D11Mapping::GetPixelFormat(EnumPixelFormat pixelFormat)
{
	switch (pixelFormat)
	{
	case PF_B8G8R8A8:
		return DXGI_FORMAT_B8G8R8A8_UNORM;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

EnumPixelFormat HrD3D11Mapping::GetPixelFormat(DXGI_FORMAT dxPixelFormat)
{
	//todo
	return PF_R8G8B8A8;

	switch (dxPixelFormat)
	{
	case DXGI_FORMAT_UNKNOWN:
		break;
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		break;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32_SINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_SNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		break;
	case DXGI_FORMAT_R32G32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32_UINT:
		break;
	case DXGI_FORMAT_R32G32_SINT:
		break;
	case DXGI_FORMAT_R32G8X24_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		break;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		break;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		break;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		break;
	case DXGI_FORMAT_R10G10B10A2_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10A2_UINT:
		break;
	case DXGI_FORMAT_R11G11B10_FLOAT:
		break;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		break;
	case DXGI_FORMAT_R8G8B8A8_SNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		break;
	case DXGI_FORMAT_R16G16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16_UNORM:
		break;
	case DXGI_FORMAT_R16G16_UINT:
		break;
	case DXGI_FORMAT_R16G16_SNORM:
		break;
	case DXGI_FORMAT_R16G16_SINT:
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT:
		break;
	case DXGI_FORMAT_R32_FLOAT:
		break;
	case DXGI_FORMAT_R32_UINT:
		break;
	case DXGI_FORMAT_R32_SINT:
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		break;
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		break;
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8_UNORM:
		break;
	case DXGI_FORMAT_R8G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_SNORM:
		break;
	case DXGI_FORMAT_R8G8_SINT:
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		break;
	case DXGI_FORMAT_R16_FLOAT:
		break;
	case DXGI_FORMAT_D16_UNORM:
		break;
	case DXGI_FORMAT_R16_UNORM:
		break;
	case DXGI_FORMAT_R16_UINT:
		break;
	case DXGI_FORMAT_R16_SNORM:
		break;
	case DXGI_FORMAT_R16_SINT:
		break;
	case DXGI_FORMAT_R8_TYPELESS:
		break;
	case DXGI_FORMAT_R8_UNORM:
		break;
	case DXGI_FORMAT_R8_UINT:
		break;
	case DXGI_FORMAT_R8_SNORM:
		break;
	case DXGI_FORMAT_R8_SINT:
		break;
	case DXGI_FORMAT_A8_UNORM:
		break;
	case DXGI_FORMAT_R1_UNORM:
		break;
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		break;
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
		break;
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		break;
	case DXGI_FORMAT_BC1_TYPELESS:
		break;
	case DXGI_FORMAT_BC1_UNORM:
		break;
	case DXGI_FORMAT_BC1_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC2_TYPELESS:
		break;
	case DXGI_FORMAT_BC2_UNORM:
		break;
	case DXGI_FORMAT_BC2_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC3_TYPELESS:
		break;
	case DXGI_FORMAT_BC3_UNORM:
		break;
	case DXGI_FORMAT_BC3_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC4_TYPELESS:
		break;
	case DXGI_FORMAT_BC4_UNORM:
		break;
	case DXGI_FORMAT_BC4_SNORM:
		break;
	case DXGI_FORMAT_BC5_TYPELESS:
		break;
	case DXGI_FORMAT_BC5_UNORM:
		break;
	case DXGI_FORMAT_BC5_SNORM:
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC6H_TYPELESS:
		break;
	case DXGI_FORMAT_BC6H_UF16:
		break;
	case DXGI_FORMAT_BC6H_SF16:
		break;
	case DXGI_FORMAT_BC7_TYPELESS:
		break;
	case DXGI_FORMAT_BC7_UNORM:
		break;
	case DXGI_FORMAT_BC7_UNORM_SRGB:
		break;
	case DXGI_FORMAT_AYUV:
		break;
	case DXGI_FORMAT_Y410:
		break;
	case DXGI_FORMAT_Y416:
		break;
	case DXGI_FORMAT_NV12:
		break;
	case DXGI_FORMAT_P010:
		break;
	case DXGI_FORMAT_P016:
		break;
	case DXGI_FORMAT_420_OPAQUE:
		break;
	case DXGI_FORMAT_YUY2:
		break;
	case DXGI_FORMAT_Y210:
		break;
	case DXGI_FORMAT_Y216:
		break;
	case DXGI_FORMAT_NV11:
		break;
	case DXGI_FORMAT_AI44:
		break;
	case DXGI_FORMAT_IA44:
		break;
	case DXGI_FORMAT_P8:
		break;
	case DXGI_FORMAT_A8P8:
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		break;
	case DXGI_FORMAT_P208:
		break;
	case DXGI_FORMAT_V208:
		break;
	case DXGI_FORMAT_V408:
		break;
	case DXGI_FORMAT_FORCE_UINT:
		break;
	default:
		break;
	}
}

D3D11_FILL_MODE HrD3D11Mapping::GetFillMode(EnumRasterizerFillModel fillMode)
{
	switch (fillMode)
	{
	case RFM_WIREFRAME:
		return D3D11_FILL_WIREFRAME;
	case RFM_SOLD:
		return D3D11_FILL_SOLID;
	default:
		return D3D11_FILL_SOLID;
	}
}

D3D11_CULL_MODE HrD3D11Mapping::GetCullMode(EnumRasterizerCullModel cullMode)
{
	switch (cullMode)
	{
	case RCM_CULL_NONE:
		return D3D11_CULL_NONE;
	case RCM_CULL_FRONT:
		return D3D11_CULL_FRONT;
	case RCM_CULL_BACK:
		return D3D11_CULL_BACK;
	default:
		return D3D11_CULL_NONE;
	}
}

D3D11_BLEND HrD3D11Mapping::GetBlend(EnumAlphaBlendFactor blendFactor)
{
	switch (blendFactor)
	{
	case ABF_UNKNOW:
		return D3D11_BLEND_ONE;
	case ABF_ZERO:
		return D3D11_BLEND_ZERO;
	case ABF_ONE:
		return D3D11_BLEND_ONE;
	case ABF_SCR_ALPHA:
		return D3D11_BLEND_SRC_ALPHA;
	case ABF_DST_ALPHA:
		return D3D11_BLEND_DEST_ALPHA;
	case ABF_INV_SRC_ALPHA:
		return D3D11_BLEND_INV_SRC_ALPHA;
	case ABF_INV_DST_ALPHA:
		return D3D11_BLEND_INV_DEST_ALPHA;
	case ABF_SRC_COLOR:
		return D3D11_BLEND_SRC_COLOR;
	case ABF_DST_COLOR:
		return D3D11_BLEND_DEST_COLOR;
	case ABF_INV_SRC_COLOR:
		return D3D11_BLEND_INV_SRC_COLOR;
	case ABF_INV_DST_COLOR:
		return D3D11_BLEND_INV_DEST_COLOR;
	case ABF_SRC_ALPHA_SAT:
		return D3D11_BLEND_SRC_ALPHA_SAT;
	case ABF_BLEND_FACTOR:
		return D3D11_BLEND_BLEND_FACTOR;
	case ABF_INV_BLEND_FACTOR:
		return D3D11_BLEND_INV_BLEND_FACTOR;
	case ABF_SRC1_ALPHA:
		return D3D11_BLEND_SRC1_ALPHA;
	case ABF_INV_SRC1_ALPHA:
		return D3D11_BLEND_INV_SRC1_ALPHA;
	case ABF_SRC1_COLOR:
		return D3D11_BLEND_SRC1_COLOR;
	case ABF_INV_SRC1_COLOR:
		return D3D11_BLEND_INV_SRC1_COLOR;
	default:
		BOOST_ASSERT(nullptr);
		break;
	}
}

D3D11_BLEND_OP HrD3D11Mapping::GetBlendOperation(EnumBlendOperation blendOp)
{
	switch (blendOp)
	{
	case BO_UNKNOW:
		return D3D11_BLEND_OP_ADD;
	case BO_ADD:
		return D3D11_BLEND_OP_ADD;
	case BO_SUB:
		return D3D11_BLEND_OP_SUBTRACT;
	case BO_REV_SUB:
		return D3D11_BLEND_OP_REV_SUBTRACT;
	case BO_MIN:
		return D3D11_BLEND_OP_MIN;
	case BO_MAX:
		return D3D11_BLEND_OP_MAX;
	default:
		BOOST_ASSERT(nullptr);
		break;
	}
}

D3D11_DEPTH_WRITE_MASK HrD3D11Mapping::GetDepthWriteMask(EnumDepthWriteMask writeMask)
{
	switch (writeMask)
	{
	case DWM_ZERO:
		return D3D11_DEPTH_WRITE_MASK_ZERO;
	case DWM_ALL:
		return D3D11_DEPTH_WRITE_MASK_ALL;
	default:
		return D3D11_DEPTH_WRITE_MASK_ALL;
	}
}

D3D11_COMPARISON_FUNC HrD3D11Mapping::GetComparisonFunc(EnumComparisonFunc comFunc)
{
	switch (comFunc)
	{
	case CF_NEVER:
		return D3D11_COMPARISON_NEVER;
	case CF_LESS:
		return D3D11_COMPARISON_LESS;
	case CF_EQUAL:
		return D3D11_COMPARISON_EQUAL;
	case CF_LESS_EQUAL:
		return D3D11_COMPARISON_LESS_EQUAL;
	case CF_GREATER:
		return D3D11_COMPARISON_GREATER;
	case CF_NOT_EQUAL:
		return D3D11_COMPARISON_NOT_EQUAL;
	case CF_GREATER_EQUAL:
		return D3D11_COMPARISON_GREATER_EQUAL;
	case CF_ALWAYS:
		return D3D11_COMPARISON_ALWAYS;
	default:
		return D3D11_COMPARISON_LESS;
	}
}

D3D11_STENCIL_OP HrD3D11Mapping::GetDepthStencilOperation(EnumStencilOperation stencilOp)
{
	switch (stencilOp)
	{
	case SO_KEEP:
		return D3D11_STENCIL_OP_KEEP;
	case SO_ZERO:
		return D3D11_STENCIL_OP_ZERO;
	case SO_REPLACE:
		return D3D11_STENCIL_OP_REPLACE;
	case SO_INCR_SAT:
		return D3D11_STENCIL_OP_INCR_SAT;
	case SO_DECR_SAT:
		return D3D11_STENCIL_OP_DECR_SAT;
	case SO_INVERT:
		return D3D11_STENCIL_OP_INVERT;
	case SO_INCR:
		return D3D11_STENCIL_OP_INCR;
	case SO_DECR:
		return D3D11_STENCIL_OP_DECR;
	default:
		return D3D11_STENCIL_OP_KEEP;
	}
}

D3D11_USAGE Hr::HrD3D11Mapping::GetTextureUsage(HrTexture::EnumTextureUsage usage)
{
	switch (usage)
	{
	case Hr::HrTexture::TU_GPUREAD_GPUWRITE:
		return D3D11_USAGE_DEFAULT;
	case Hr::HrTexture::TU_GPUREAD_CPUWRITE:
		return D3D11_USAGE_DYNAMIC;
	case Hr::HrTexture::TU_GPUREAD_IMMUTABLE:
		return D3D11_USAGE_IMMUTABLE;
	case Hr::HrTexture::TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE:
		return D3D11_USAGE_STAGING;
	default:
		break;
	}
}

HrTexture::EnumTextureUsage HrD3D11Mapping::GetTextureUsage(D3D11_USAGE usage)
{
	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
		return HrTexture::TU_GPUREAD_GPUWRITE;
	case D3D11_USAGE_IMMUTABLE:
		return HrTexture::TU_GPUREAD_IMMUTABLE;
	case D3D11_USAGE_DYNAMIC:
		return HrTexture::TU_GPUREAD_CPUWRITE;
	case D3D11_USAGE_STAGING:
		return HrTexture::TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE;
	default:
		break;
	}
}

