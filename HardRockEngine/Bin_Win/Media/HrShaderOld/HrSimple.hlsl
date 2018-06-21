#include "HrLightingCommon.hlsl"

cbuffer cbPerFrame
{
	uint4 lightsNum;
	float4 ambientLightColor;
	DirectionLight directLight[4];

	float3 camera_position;
};

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 view_proj_matrix;
    Material mat;
};

Texture2D gTexture0;

SamplerState gSampler0
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VertexOut
{
	float4 posWorldViewProj : SV_POSITION;
    float4 posWorld : POSITION;
    float3 pixWorldNormal : NORMAL;
    float2 uv : TEXCOORD;
};

VertexOut Pass0_VS_Main(VertexIn vIn)
{
    VertexOut vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
    vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	//·¨Ïß±ä»»
    vOut.pixWorldNormal = normalize(mul(float4(vIn.vertexNormal, 0.0f), transpose(world_matrix)).xyz);
    vOut.uv = vIn.uv;

    return vOut;
}

float4 Pass0_PS_Main(VertexOut pixIn) : SV_TARGET
{
    float4 worldCameraPos = float4(camera_position, 1.0);
    float3 viewDir = normalize(worldCameraPos - pixIn.posWorld);

    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    rtAmbient = mat.ambient_material_color * ambientLightColor;

    for (uint i = 0; i < lightsNum[0]; ++i)
    {
        float3 lightDir = normalize(-directLight[i].light_direction.xyz);
        float fDiffuseFactor = max(0, dot(lightDir, pixIn.pixWorldNormal));
        rtDiffuse += float4(fDiffuseFactor * mat.diffuse_material_color.xyz * directLight[i].diffuse_light_color.xyz, 0.0);


        float3 reflectSpecularDir = normalize(2 * dot(lightDir, pixIn.pixWorldNormal) * pixIn.pixWorldNormal - lightDir);
        rtSpecular += mat.specular_material_color * directLight[i].specular_light_color * pow(max(dot(viewDir, reflectSpecularDir), 0), mat.glossiness_material);
    }


    //float4 texColor = gTexture0.Sample(gSampler0, pixIn.texCoord);
    //float4 pixColor = texColor * (rtAmbient + rtDiffuse) + rtSpecular;
    float4 pixColor = rtAmbient + rtDiffuse + rtSpecular;

    return pixColor;
}

