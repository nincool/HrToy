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

