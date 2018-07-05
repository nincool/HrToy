#include "HrCommonInput.hlsl"
#include "HrCommonOutput.hlsl"
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
    float4x4 view_proj_matrix;
    Material mat;
};

HrVertexOutputStandard1 StandardVSInputPN(HrVertexInputPN vIn)
{
	HrVertexOutputStandard1 vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
	//法线变换
	vOut.pixWorldNormal = normalize(mul(float4(vIn.vertexNormal, 0.0f), transpose(world_matrix)).xyz);

    return vOut;
}

HrVertexOutputStandard1 StandardVSInputPNC(HrVertexInputPNC vIn)
{
    HrVertexOutputStandard1 vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
    vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	//法线变换
    vOut.pixWorldNormal = normalize(mul(float4(vIn.vertexNormal, 0.0f), transpose(world_matrix)).xyz);

    return vOut;
}

float4 StandardPSOuput1(HrVertexOutputStandard1 pixIn) : SV_TARGET
{
    float4 worldCameraPos = float4(camera_position, 1.0);
    float3 viewDir = normalize(worldCameraPos - pixIn.posWorld);

    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    if (lightsNum.x == 1)
        rtAmbient = mat.ambient_material_color * ambientLightColor;

    float4 pixColor = rtAmbient;

    for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
    {
        pixColor += CalcDirectionLight(directLight[nDirLightIndex], worldCameraPos, pixIn.posWorld, pixIn.pixWorldNormal, mat);
    }

    for (uint nPointLightIndex = 0; nPointLightIndex < lightsNum.z; ++nPointLightIndex)
    {
        pixColor += CalcPointLight(pointLight[nPointLightIndex], worldCameraPos, pixIn.posWorld, pixIn.pixWorldNormal, mat);
    }

    return pixColor;
}

