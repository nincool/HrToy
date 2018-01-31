
#include "HrLightingCommon.fx"


cbuffer cbPerFrame
{
    float4 ambientLightColor;
    DirectionLight directLight;
};

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 world_view_proj_matrix;
    float4x4 inverse_transpose_world_matrix;
    Material mat;
};

struct VertexIn
{
    float3 vertexPosition : POSITION;
    float3 vertexNormal : NORMAL;
    float2 textureCoord : TEXCOORD;
};

struct VertexOut
{
    float4 posWorldViewProj : SV_POSITION;
    float4 pixelColor : COLOR;
};

VertexOut VS_Main(VertexIn vIn)
{
    VertexOut vOut;
    
    //·¨Ïß±ä»»
    float3 normalDirection = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);

    float3 reflectLightDir = normalize(-directLight.light_direction[0]);
    float fDiffuseFactor = dot(reflectLightDir, normalDirection);
    float4 fAmbient = mat.ambient_material_color * ambientLightColor;
    float4 fDiffuse = fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color[0];

    //vout.posTrans = mul(float4(v.vertexPosition, 1.f), world_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);
    //vout.normal = normalDirection;
    //vout.color = fAmbient + fDiffuse;

    fDiffuse.w = 1;
    vOut.pixelColor = fDiffuse + fAmbient;

    return vOut;
}

float4 PS_Main(VertexOut pixIn) : SV_TARGET
{
    //float4 texColor = g_tex.Sample(samTex, pin.tex);

    return pixIn.pixelColor;
}





