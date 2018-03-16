#include "HrLightingCommon.hlsl"

cbuffer cbPerFrame
{
	uint4 lightsNum;
	float4 ambientLightColor;
	DirectionLight directLight[4];
	PointLight pointLight[4];

	float3 camera_position;
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

VertexOut Pass0_VS_Main(VertexIn vIn)
{
	VertexOut vOut;

	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);

	//·¨Ïß±ä»»
	float3 normalDirection = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
	float3 worldCameraPos = camera_position;
	float3 posWorldTranslate = mul(float4(vIn.vertexPosition, 1.0f), world_matrix).xyz;
	float3 viewDir = normalize(worldCameraPos - posWorldTranslate);


	float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

	rtAmbient = mat.ambient_material_color * ambientLightColor;

    for (uint i = 0; i < lightsNum[0]; ++i)
    {
        float3 lightDir = normalize(-directLight[i].light_direction.xyz);
        float fDiffuseFactor = max(0, dot(lightDir, normalDirection));
        rtDiffuse += float4(fDiffuseFactor * mat.diffuse_material_color.xyz * directLight[i].diffuse_light_color.xyz, 0.0);


        float3 reflectSpecularDir = normalize(2 * dot(lightDir, normalDirection) * normalDirection - lightDir);
        rtSpecular += mat.specular_material_color * directLight[i].specular_light_color * pow(max(dot(viewDir, reflectSpecularDir), 0), mat.glossiness_material);
    }
	vOut.pixelColor = rtAmbient + rtDiffuse + rtSpecular;

	return vOut;
}

float4 Pass0_PS_Main(VertexOut pixIn) : SV_TARGET
{
	return pixIn.pixelColor;
}

