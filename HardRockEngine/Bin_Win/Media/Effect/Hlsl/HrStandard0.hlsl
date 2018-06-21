#include "HrCommonInput.hlsl"
#include "HrCommonOutput.hlsl"
#include "HrCommonLights.hlsl"

cbuffer cbPerFrame
{
	float4 ambientLightColor;
};

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 view_proj_matrix;
    Material mat;
};

HrVertexOutputStandard0 StandardVS(HrVertexInputP vIn)
{
    HrVertexOutputStandard0 vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);

    return vOut;
}

float4 StandardPS(HrVertexOutputStandard0 pixIn) : SV_TARGET
{
    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };

    rtAmbient = mat.ambient_material_color * ambientLightColor;

    float4 pixColor = rtAmbient;

    return pixColor;
}

