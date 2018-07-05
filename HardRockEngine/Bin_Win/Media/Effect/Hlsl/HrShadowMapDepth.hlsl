#include "HrCommonInput.hlsl"
#include "HrCommonOutput.hlsl"

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 view_proj_matrix;
};


HrVertexOutputStandard1 ShadowMapDepthVS(HrVertexInputPNC vIn)
{
    HrVertexOutputStandard1 vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
    vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

    return vOut;
}

float4 ShadowMapDepthPS(HrVertexOutputStandard1 pixIn) : SV_TARGET
{
    return float4(0, 0, 0, 0);
}

