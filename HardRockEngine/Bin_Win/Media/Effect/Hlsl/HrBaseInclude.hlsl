
struct HrVertexInput_P
{
	float3 vertexPosition : POSITION;
};

struct HrVertexInput_P_C
{
	float3 vertexPosition : POSITION;
	float3 color : COLOR;
};

struct HrVertexInput_P_N
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
};

struct HrVertexInput_P_N_UV
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
	float2 vertexCoord : TEXCOORD0;
};

struct HrVertexInput_P_UV_T_N
{
    float3 vertexPosition : POSITION;
    float2 vertexTexcoord : TEXCOORD0;
    float3 vertexTangent : TANGENT;
    float3 vertexNormal : NORMAL;
};

struct HrVertexInput_P_T_B_N_UV
{
	float3 vertexPosition : POSITION;
	float3 vertexTangent : TANGENT;
	float3 vertexBinormal : BINORMAL;
	float3 vertexNormal : NORMAL;
	float2 vertexTexcoord : TEXCOORD0;
};

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

struct HrPixelInput_PWVP
{
    float4 posWorldViewProj : SV_POSITION;
};

struct HrPixelInput_PWVP_C
{
    float4 posWorldViewProj : SV_POSITION;
    float4 color : COLOR;
};

struct HrPixelInput_PWVP_PW_NW
{
    float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
};

struct HrPixelInput_PWVP_PW_NW_UV
{
    float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float2 uv : TEXCOORD;
};

struct HrPixelInput_PWVP_PW_NW_TW_UV
{
    float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float3 tangentWorld : TANGENT;
    float2 uv : TEXCOORD;
};

struct HrPixelInput_PWVP_UV_NW_TW_BW_PW
{
    float4 posWorldViewProj : SV_POSITION;
    float2 uv0 : TEXCOORD0;
    float3 normalWorld : TEXCOORD1;
    float3 tangentWorld : TEXCOORD2;
    float3 binormalWorld : TEXCOORD3;
    float4 posWorld : TEXCOORD4;
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

