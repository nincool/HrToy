struct HrVertexOutputStandard4
{
    float4 posWorldViewProj : SV_POSITION;
};

struct HrVertexOutputStandard1
{
	float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 pixWorldNormal : NORMAL;
};

struct HrVertexOutputStandard2
{
	float4 posWorldViewProj : SV_POSITION;
	float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
	float2 uv : TEXCOORD;
};

struct HrVertexOutputStandard3
{
    float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float3 tangentWorld : TANGENT;
    float2 uv : TEXCOORD;
};

struct HrPixelInputPWVP
{
    float4 posWorldViewProj : SV_POSITION;
};

struct HrPixelInputPWVP_PW_NW
{
	float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
};

struct HrPixelInputPWVP_PW_NW_UV
{
	float4 posWorldViewProj : SV_POSITION;
	float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
	float2 uv : TEXCOORD;
};

struct HrPixelInputPWVP_PW_NW_TW_UV
{
    float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float3 tangentWorld : TANGENT;
    float2 uv : TEXCOORD;
};



struct HrVertexOutputGBuffer1
{
	float4 posWorldViewProj : SV_POSITION;
	float4 posWorld : POSITION;
	float3 normalWorld : NORMAL;
	float2 uv : TEXCOORD;

};

struct HrPixelOutputGBuffer1
{
	float4 posGBuffer : SV_TARGET0;
	float4 normalGBuffer : SV_TARGET1;
	float4 albedoGBuffer : SV_TARGET2;
};