
#include "HrLightingCommon.fx"

//cbuffer cbPerFrame
//{
//    DirectionLight directLight;
//};
//
//cbuffer cbPerObject
//{
//    float4x4 world_view_proj_matrix;
//    //float4x4 inverse_transpose_world_matrix;
//    //Material mat;
//};
//
//struct VertexIn
//{
//    float3 posVertexIn : POSITIONT;
//    float3 normal : NORMAL;
//};
//
//struct VertexOut
//{
//    float4 posVextexOut : SV_POSITION;
//    float4 col : COLOR;
//};
//
//VertexOut VS_Main(VertexIn v)
//{
//    VertexOut o;
//    //float3 normalDirection = normalize(mul(float4(v.normal, 0.0f), inverse_transpose_world_matrix).xyz);
//
//    //float3 reflectLightDir = normalize(-directLight.light_direction);
//    //float fDiffuseFactor = dot(reflectLightDir, normalDirection);
//
//    //float4 fAmbient = mat.ambient_material_color * directLight.ambient_light_color;
//
//    //float4 fDiffuse = fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color;
//
//    o.posVextexOut = mul(float4(v.posVertexIn, 1.0f), world_view_proj_matrix);
//    //o.col = fAmbient + fDiffuse;
//    //o.col.a = mat.diffuse_material_color.a;
//
//    o.col = float4(1.0, 0.0, 0.0, 1.0);//directLight.ambient_light_color;
//    o.col.a = 1.0;//mat.diffuse_material_color.a;
//
//    return o;
//}
//
//float4 PS_Main(VertexOut o) : SV_Target
//{
//    return o.col;
//}
//

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

struct VertexIn
{
    float3	pos 	: POSITION;
    float3	normal 	: NORMAL;
    float4      color   : COLOR;
};

struct VertexOut
{
    float4	posH	: SV_POSITION;
    float4	color	: COLOR;
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
	//vout.color = fDiffuseFactor;
	//vout.color = float4(1.0, fDiffuseFactor, 0.0, 1.0);

    return vout;
}

float4 PS_Main(VertexOut pin) :SV_TARGET
{
    return pin.color;
}





