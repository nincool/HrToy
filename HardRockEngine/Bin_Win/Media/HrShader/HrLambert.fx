
#include "HrLightingCommon.fx"

cbuffer cbPerFrame
{
    DirectionLight directLight;
};

cbuffer cbPerObject
{
    float4x4 worldInvTranspose_matrix;
    float4x4 worldviewproj_matrix;
    Material mat;
};

struct VertexIn
{
    float3 posVertexIn : POSITIONT;
    float3 normal : NORMAL;
};

struct VertexOut
{
    float4 posVextexOut : SV_POSITION;
    float4 col : COLOR;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut o;
    float3 normalDirection = normalize(mul(float4(v.normal, 0.0f), worldInvTranspose_matrix).xyz);

    float3 reflectLightDir = normalize(-directLight.fDirection);
    float fDiffuseFactor = dot(reflectLightDir, normalDirection);

    float4 fAmbient = mat.fAmbient * directLight.fAmbient;

    float4 fDiffuse = fDiffuseFactor * mat.fDiffuse * directLight.fDiffuse;

    o.posVextexOut = mul(float4(v.posVertexIn, 1.0f), worldviewproj_matrix);
    o.col = fAmbient + fDiffuse;
    o.col.a = mat.fDiffuse.a;


    return o;
}

float4 PS_Main(VertexOut o) : SV_Target
{
    return o.col;
}





