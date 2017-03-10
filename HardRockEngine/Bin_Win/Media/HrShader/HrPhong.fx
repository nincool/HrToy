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

    float3 camera_position;
};

//纹理
Texture2D g_tex;
//设置过滤
SamplerState samTex
{
    Filter = MIN_MAG_MIP_LINEAR;
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

///////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////
VertexOut Pass0_VS_Main(VertexIn vIn)
{
    VertexOut vOut;
    
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);

    //法线变换
    float3 normalDirection = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);

    float3 reflectLightDir = normalize(-directLight.light_direction[0]);
    float fDiffuseFactor = max(0, dot(reflectLightDir, normalDirection));
    float4 fAmbient = mat.ambient_material_color * ambientLightColor;
    float4 fDiffuse = fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color[0];

    float3 curWorldPos = vOut.posWorldViewProj.xyz;
    float3 viewDir = normalize(camera_position - curWorldPos);
    float3 reflectSpecularDir = normalize(2 * normalDirection - reflectLightDir);
    float4 specularColor = mat.specular_material_color * directLight.specular_light_color[0] * pow(max(dot(viewDir, reflectSpecularDir), 0), 5);

    vOut.pixelColor = fDiffuse + fAmbient + specularColor;

    return vOut;
}

float4 Pass0_PS_Main(VertexOut pixIn) : SV_TARGET
{
    return pixIn.pixelColor;
}

///////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////
VertexOut Pass1_VS_Main(VertexIn vIn)
{
    VertexOut vOut;
    
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);

    //法线变换
    float3 normalDirection = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);

    float3 reflectLightDir = normalize(-directLight.light_direction[0]);
    float fDiffuseFactor = max(0, dot(reflectLightDir, normalDirection));
    float4 fAmbient = mat.ambient_material_color * ambientLightColor;
    float4 fDiffuse = fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color[0];

    float3 curWorldPos = vOut.posWorldViewProj.xyz;
    float3 viewDir = normalize(camera_position - curWorldPos);
    float3 halfViewLight = normalize(viewDir + reflectLightDir);
    float4 specularColor = mat.specular_material_color * directLight.specular_light_color[0] * pow(max(dot(halfViewLight, normalDirection), 0), 10);

    vOut.pixelColor = fDiffuse + fAmbient + specularColor;

    return vOut;
}

float4 Pass1_PS_Main(VertexOut pixIn) : SV_TARGET
{
    return pixIn.pixelColor;
}





