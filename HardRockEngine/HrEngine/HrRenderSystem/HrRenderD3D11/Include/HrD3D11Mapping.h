#ifndef _HR_D3D11MAPPING_H_
#define _HR_D3D11MAPPING_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Texture.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Render/HrBlendState.h"
#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrCore/Include/Render/HrRasterizerState.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11Mapping
	{
	public:
		//InputElement SemanticName <=> EnumVertexElementSemantic
		static LPCSTR GetInputElementSemanticName(EnumVertexElementSemantic usage);
		static EnumVertexElementSemantic GetInputElementSemanticName(const std::string& strSemantic);

		static DXGI_FORMAT GetInputElementFormat(EnumVertexElementType type);
		
		//D3D11_INPUT_CLASSIFICATION <=> EnumVertexElementClassType
		static D3D11_INPUT_CLASSIFICATION GetInputElementClassType(EnumVertexElementClassType type);
		
		//topology
		static D3D_PRIMITIVE_TOPOLOGY GetTopologyType(EnumTopologyType topologyType);
		
		//Ë÷Òý»º´æ¸ñÊ½
		static DXGI_FORMAT GetIndexBufferFormat(EnumIndexType indexType);

		//Shader Data type
		static EnumRenderEffectDataType GetRenderParamDataType(D3D_SHADER_VARIABLE_TYPE shaderVariableType, int nRows, int nCols);
		static uint32 GetRenderParamDataSize(EnumRenderEffectDataType shaderVariableType);
		
		//D3D11_USAGE <=> HrGraphicsBuffer::EnumGraphicsBufferUsage
		static D3D11_USAGE GetGraphicsUsage(HrGraphicsBuffer::EnumGraphicsBufferUsage usage);
		static UINT GetCPUAccessFlag(HrGraphicsBuffer::EnumGraphicsBufferUsage usage);
		static D3D11_BIND_FLAG GetGraphicsBindFlag(HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag);

		static D3D11_MAP GetBufferMap(HrGraphicsBuffer::EnumGraphicsBufferUsage usage, HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag);
		
		//DXGI_FORMAT <=> EnumPixelFormat
		static DXGI_FORMAT GetPixelFormat(EnumPixelFormat pixelFormat);
		static EnumPixelFormat GetPixelFormat(DXGI_FORMAT dxPixelFormat);
		
		static D3D11_FILL_MODE GetFillMode(EnumRasterizerFillModel fillMode);
		static D3D11_CULL_MODE GetCullMode(EnumRasterizerCullModel cullMode);

		//depthstencil
		static D3D11_DEPTH_WRITE_MASK GetDepthWriteMask(EnumDepthWriteMask writeMask);
		static D3D11_COMPARISON_FUNC GetComparisonFunc(EnumComparisonFunc comFunc);
		static D3D11_STENCIL_OP GetDepthStencilOperation(EnumStencilOperation stencilOp);

		//D3D11_BLEND <=> EnumAlphaBlendFactor
		static D3D11_BLEND GetBlend(EnumAlphaBlendFactor blendFactor);
		//D3D11_BLEND_OP <=> EnumBlendOperation
		static D3D11_BLEND_OP GetBlendOperation(EnumBlendOperation blendOp);
		//D3D11WriteMask
		static UINT8 GetRenderTargetWriteMask(uint8 colorMask);

		//HrTexture::EnumTextureUsage <=> D3D11_USAGE
		static D3D11_USAGE GetTextureUsage(HrTexture::EnumTextureUsage usage);
		static HrTexture::EnumTextureUsage GetTextureUsage(D3D11_USAGE usage);

		//D3D11_FILTER <=> EnumSamplerFilter
		static D3D11_FILTER GetFilter(EnumSamplerFilter filter);
		
		//D3D11_TEXTURE_ADDRESS_MODE <=> EnumTextureAddressMode
		static D3D11_TEXTURE_ADDRESS_MODE GetTextureAddressMode(EnumTextureAddressMode addressMode);
	};
}

#endif




