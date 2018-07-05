#include "HrCommonInput.hlsl"
#include "HrCommonLights.hlsl"

struct HrVertexOutputStandard1
{
		float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION0;
    float4 pointWorldViewProj : POSITION1;
    float3 pixWorldNormal : NORMAL;
};

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
	float4x4 view_proj_matrix;
	float4x4 point_view_proj_matrix;
	Material mat;
};

Texture2D texShadowMap;  //投影纹理

SamplerState samShadow
{
	Filter = COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	AddressU = BORDER;
	AddressV = BORDER;
	AddressW = BORDER;
	BorderColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComparisonFunc = LESS;
};


HrVertexOutputStandard1 ShadowMapVS(HrVertexInputPNC vIn)
{
	HrVertexOutputStandard1 vOut;

	float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
	vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	float4x4 pointWorldViewProjMatrix = mul(world_matrix, point_view_proj_matrix);
	vOut.pointWorldViewProj = mul(float4(vIn.vertexPosition, 1.0f), pointWorldViewProjMatrix);
	//法线变换
	vOut.pixWorldNormal = normalize(mul(float4(vIn.vertexNormal, 0.0f), transpose(world_matrix)).xyz);

	return vOut;
}

float4 ShadowMapPS(HrVertexOutputStandard1 pixIn) : SV_TARGET
{
	float2 shadowTex;//阴影纹理坐标
	shadowTex.x = pixIn.pointWorldViewProj.x / pixIn.pointWorldViewProj.w * 0.5f + 0.5f;
	shadowTex.y = pixIn.pointWorldViewProj.y / pixIn.pointWorldViewProj.w * (-0.5f) + 0.5f;

	float bias = 0.0001f;

	float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };


	if (lightsNum.x == 1)
		rtAmbient = mat.ambient_material_color * ambientLightColor;

	float4 pixColor = rtAmbient;

	if (saturate(shadowTex.x) == shadowTex.x && saturate(shadowTex.y) == shadowTex.y)
	{
		float shadowMapDepth = texShadowMap.Sample(samShadow, shadowTex).r;

		float depth = pixIn.pointWorldViewProj.z / pixIn.pointWorldViewProj.w;

		depth = depth - bias;

		if (shadowMapDepth >= depth)
		{
			float4 worldCameraPos = float4(camera_position, 1.0);
			float3 viewDir = normalize(worldCameraPos - pixIn.posWorld);

			for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
			{
				pixColor += CalcDirectionLight(directLight[nDirLightIndex], worldCameraPos, pixIn.posWorld, pixIn.pixWorldNormal, mat);
			}

			for (uint nPointLightIndex = 0; nPointLightIndex < lightsNum.z; ++nPointLightIndex)
			{
				pixColor += CalcPointLight(pointLight[nPointLightIndex], worldCameraPos, pixIn.posWorld, pixIn.pixWorldNormal, mat);
			}
		}
	}

	return pixColor;
}

