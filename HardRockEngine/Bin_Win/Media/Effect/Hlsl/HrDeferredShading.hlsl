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

Texture2D texGBufferPos;
Texture2D texGBufferNormal;
Texture2D texGBufferAlbedo;

SamplerState samBaseTexture;

void GetAttributes(in float2 screenPos, out float3 pos, out float3 normal, out float3 albedo, out float glossiness)
{
	int3 nIndex = int3(screenPos.xy, 0);
	pos = texGBufferPos.Load(nIndex).xyz;
	normal = texGBufferNormal.Load(nIndex).xyz;
	float4 albedoGlossiness = texGBufferAlbedo.Load(nIndex);
	albedo = albedoGlossiness.xyz;
	glossiness = albedoGlossiness.w;
}

float4 DeferredVSP(float3 pos : POSITION) : SV_POSITION
{
	return float4(pos, 1.0f);
}

float4 DeferredPS(float4 pos : SV_POSITION) : SV_TARGET
{
	float3 normalWorld;
	float3 posWorld;
	float3 albedo;
	float glossiness;

	GetAttributes(pos, posWorld, normalWorld, albedo, glossiness);

	float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

	if (lightsNum.x == 1)
		rtAmbient = mat.material_albedo * ambientLightColor;

	float4 pixColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
	{
		float4 diffuse;
		float4 specular;
		CalcDirectionLightSplitDeferred(directLight[nDirLightIndex], camera_position, posWorld, normalWorld, glossiness, diffuse, specular);
		rtDiffuse += diffuse;
		rtSpecular += specular;
	}

	//pixColor = rtAmbient + rtDiffuse + rtSpecular;
	pixColor = float4(albedo, 1.0);

	return pixColor;
}

