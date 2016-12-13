
#include "HrLightingCommon.fx"


cbuffer cbPerFrame
{
    DirectionLight directLight;
};

cbuffer cbPerObject
{
    float4x4 world_view_proj_matrix;
    float4x4 inverse_transpose_world_matrix;
    Material mat;
};

//Œ∆¿Ì
Texture2D g_tex;
//…Ë÷√π˝¬À
SamplerState samTex
{
		Filter = MIN_MAG_MIP_LINER;
};

struct VertexIn
{
    float3	pos 	: POSITION;
    float3	normal 	: NORMAL;
    float2  tex : TEXCOORD;
};

struct VertexOut
{
    float4	posH	: SV_POSITION;
    float4	color	: COLOR;
    float2  tex : TEXCOORD;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut vout;
    
    float3 normalDirection = normalize(mul(float4(v.normal, 0.0f), inverse_transpose_world_matrix).xyz);
    float3 reflectLightDir = normalize(-directLight.light_direction);
    float fDiffuseFactor = dot(reflectLightDir, normalDirection);
	float4 fAmbient = mat.ambient_material_color * directLight.ambient_light_color;
	float4 fDiffuse = fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color;

    vout.posH = mul(float4(v.pos, 1.f), world_view_proj_matrix);
    vout.color = fAmbient + fDiffuse;
    vout.tex = v.tex;
    //vout.color = float4(normalDirection, 1.0);
	//vout.color = fDiffuseFactor;
	//vout.color = float4(1.0, fDiffuseFactor, 0.0, 1.0);

    return vout;
}

float4 PS_Main(VertexOut pin) :SV_TARGET
{

		float4 texColor = g_tex.Sample(samTex, pin.tex);
		float4 finalColor = texColor * pin.color;
    return finalColor;
}





