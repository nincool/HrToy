#include "HrCommonInput.hlsl"
#include "HrCommonLights.hlsl"

cbuffer cbPerFrame
{
	float4 ambientLightColor;
	uint4 lightsNum;
	DirectionLight directLight[4];
	PointLight pointLight[4];

	float3 camera_position;
};

cbuffer cbPerObject
{
	float4x4 world_matrix;
	float4x4 inverse_transpose_world_matrix;
	float4x4 view_proj_matrix;
	Material mat;
};

Texture2D texAlbedo;
Texture2D texGBufferPos;
Texture2D texGBufferNormal;
Texture2D texGBufferAlbedo;

SamplerState samBaseTexture;

HrVertexOutputGBuffer1 GBuffersVSP(HrVertexInput_P vIn)
{
	HrVertexOutputGBuffer1 vOut;
	float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.0f), worldViewProjMatrix);
	vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	vOut.normalWorld = float3(0.0, 0.0, 0.0);
	vOut.uv = float2(0.0, 0.0);

	return vOut;
}

HrVertexOutputGBuffer1 GBuffersVSPN(HrVertexInput_P_N vIn)
{
	HrVertexOutputGBuffer1 vOut;
	float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.0f), worldViewProjMatrix);
	vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	vOut.normalWorld = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
	vOut.uv = float2(0.0, 0.0);

	return vOut;
}

HrVertexOutputGBuffer1 GBuffersVSPNC(HrVertexInput_P_N_UV vIn)
{
	HrVertexOutputGBuffer1 vOut;
	float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.0f), worldViewProjMatrix);
	vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	vOut.normalWorld = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
	vOut.uv = vIn.vertexCoord;

	return vOut;
}

HrPixelOutputGBuffer1 GBuffersPS1(HrVertexOutputGBuffer1 pixIn)
{
	HrPixelOutputGBuffer1 pOut;
	float4 texColor = texAlbedo.Sample(samBaseTexture, pixIn.uv);
	pOut.posGBuffer = float4(pixIn.posWorld);
	pOut.normalGBuffer = float4(normalize(pixIn.normalWorld), 0.0f);
	pOut.albedoGBuffer = texColor;

	return pOut;
}

