#include "HrCommonInput.hlsl"
#include "HrCommonLights.hlsl"

cbuffer cbPerFrame
{
	float4 ambientLightColor;
	uint4 lightsNum;
	DirectionLight directLight[4];
    PointLight pointLight[4];

	float3 camera_position;
};

cbuffer cbPerObject
{    
    float4x4 world_matrix;
    float4x4 inverse_transpose_world_matrix;
    float4x4 view_proj_matrix;
    float4x4 world_view_proj_matrix;
    Material mat;
};

Texture2D texAlbedo;
Texture2D texMetallic;
Texture2D texNormal;

SamplerState samBaseTexture;

HrPixelInput_PWVP StandardVSInputP(HrVertexInput_P vIn)
{
    HrPixelInput_PWVP vOut;

	float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
	vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);

	return vOut;
}

float4 StandPSPWVP(HrPixelInput_PWVP pixIn) : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

HrPixelInput_PWVP_C StandardVSInputPC(HrVertexInput_P_C vIn)
{
    HrPixelInput_PWVP_C vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.0), worldViewProjMatrix);
    vOut.color = float4(vIn.color, 1.0f);

    return vOut;
}

float4 StandPSPWVP_C(HrPixelInput_PWVP_C pixIn) : SV_TARGET
{
    return pixIn.color;
}

HrPixelInput_PWVP_PW_NW StandardVSInputPN(HrVertexInput_P_N vIn)
{
    HrPixelInput_PWVP_PW_NW vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), worldViewProjMatrix);
	//法线变换
    vOut.normalWorld = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
	vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

    return vOut;
}

float4 StandPSPWVP_PW_NW(HrPixelInput_PWVP_PW_NW pixIn) : SV_TARGET
{
    float4 worldCameraPos = float4(camera_position, 1.0);
    float3 viewDir = normalize(worldCameraPos - pixIn.posWorld).xyz;

    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    if (lightsNum.x == 1)
        rtAmbient = mat.material_albedo * ambientLightColor;

    float4 pixColor = rtAmbient;

    for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
    {
        pixColor += CalcDirectionLight(directLight[nDirLightIndex], worldCameraPos, pixIn.posWorld, pixIn.normalWorld, mat);
    }

    for (uint nPointLightIndex = 0; nPointLightIndex < lightsNum.z; ++nPointLightIndex)
    {
        pixColor += CalcPointLight(pointLight[nPointLightIndex], worldCameraPos, pixIn.posWorld, pixIn.normalWorld, mat);
    }

    return pixColor;
}

HrPixelInput_PWVP_PW_NW_UV StandardVSInputPNC(HrVertexInput_P_N_UV vIn)
{
    HrPixelInput_PWVP_PW_NW_UV vOut;

    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);
    vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

	//法线变换
    vOut.normalWorld = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
    vOut.uv = vIn.vertexCoord;

    return vOut;
}

//normal diffuse
float4 StandPSPWVP_PW_NW_UV(HrPixelInput_PWVP_PW_NW_UV pixIn) : SV_TARGET
{
    //float4 worldCameraPos = float4(camera_position, 1.0);
    //float3 viewDir = normalize(worldCameraPos - pixIn.posWorld).xyz;

    //float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
    //float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
    //float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    //if (lightsNum.x == 1)
    //    rtAmbient = mat.material_albedo * ambientLightColor;

    float4 pixColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
    //{
    //    float4 diffuse;
    //    float4 specular;
    //    CalcDirectionLightSplit(directLight[nDirLightIndex], worldCameraPos, pixIn.posWorld, pixIn.normalWorld, mat, diffuse, specular);
    //    rtDiffuse += diffuse;
    //    rtSpecular += specular;
    //}

    //for (uint nPointLightIndex = 0; nPointLightIndex < lightsNum.z; ++nPointLightIndex)
    //{
    //    float4 diffuse;
    //    float4 specular;
    //    CalcPointLightSplit(pointLight[nPointLightIndex], worldCameraPos, pixIn.posWorld, pixIn.normalWorld, mat, diffuse, specular);
    //    rtDiffuse += diffuse;
    //    rtSpecular += specular;
    //}

    //if (flag_use_basetex != 0)
    //{
    //    float4 texColor = float4(1, 1, 1, 1);
    //    texColor = texAlbedo.Sample(samBaseTexture, pixIn.uv);
    //    pixColor = texColor * (rtAmbient + rtDiffuse) + rtSpecular;
    //}
    //else
    //{
    //    pixColor = rtAmbient + rtDiffuse + rtSpecular;
    //}

    return pixColor;
}

//struct HrVertexInput_P_T_B_N_UV
//{
//    float3 vertexPosition : POSITION;
//    float3 vertexTangent : TANGENT;
//    float3 vertexBinormal : BINORMAL;
//    float3 vertexNormal : NORMAL;
//    float2 vertexCoord : TEXCOORD0;
//};

//struct HrPixelInput_PWVP_UV_NW_TW_BW_PW
//{
//    float4 posWorldViewProj : SV_POSITION;
//    float3 uv0 : TEXCOORD0;
//    float3 normalWorld : TEXCOORD1;
//    float3 tangentWorld : TEXCOORD2;
//    float3 binormalWorld : TEXCOORD3;
//    float4 posWorld : TEXCOORD4;
//};

//struct Material
//{
//    float4 material_albedo;
//    float material_metallic;
//    float material_roughness;
//    uint material_param0;
//    uint material_param1;
//};


HrPixelInput_PWVP_UV_NW_TW_BW_PW StandardVSInput_PTBNC(HrVertexInput_P_T_B_N_UV vIn)
{
    HrPixelInput_PWVP_UV_NW_TW_BW_PW vOut;

    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition, 1.f), world_view_proj_matrix);

    vOut.uv0 = vIn.vertexTexcoord;
    vOut.normalWorld = normalize(mul(float4(vIn.vertexNormal, 0.0f), inverse_transpose_world_matrix).xyz);
    vOut.tangentWorld = normalize(mul(float4(vIn.vertexTangent, 0.0), world_matrix).xyz);
    vOut.binormalWorld = normalize(cross(vOut.normalWorld, vOut.tangentWorld));
    
    vOut.posWorld = mul(float4(vIn.vertexPosition, 1.0f), world_matrix);

    return vOut;
}

//float3 CalcPBRDirectionLightSplit(DirectionLight directLight, float3 normalDir, float3 viewDir, float3 albedo, float roughness, float metalness)
//normal map
float4 StandPS_PWVP_UV_NW_TW_BW_PW(HrPixelInput_PWVP_UV_NW_TW_BW_PW pixIn) : SV_TARGET
{
    float4 worldCameraPos = float4(camera_position, 1.0);
    float3 viewDir = normalize(worldCameraPos - pixIn.posWorld).xyz;
    float3 normalDir = normalize(pixIn.normalWorld);

    int nNormalmapUsed = mat.material_param0 & 1;

    //Normal mapping
    if (nNormalmapUsed != 0)
    {
        float3 normalMapSample = texNormal.Sample(samBaseTexture, pixIn.uv0).rgb;
        normalDir = NormalSampleToWorldSpaceTBN(normalMapSample, pixIn.tangentWorld, pixIn.binormalWorld, pixIn.normalWorld);
    }
    
    //float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
    //if (lightsNum.x == 1)
    //    rtAmbient = mat.material_albedo * ambientLightColor;

    float4 albedo = texAlbedo.Sample(samBaseTexture, pixIn.uv0);
    float4 metalTex = texMetallic.Sample(samBaseTexture, pixIn.uv0);
  
    float metalness = metalTex.r; //grayscale value 存在r通道
    float roughness = 1 - metalTex.a; //在Metallicmap的alpha通道里存的是smoothness

    float3 finalColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    for (uint nDirLightIndex = 0; nDirLightIndex < lightsNum.y; ++nDirLightIndex)
    {
        finalColor += CalcPBRDirectionLight(directLight[nDirLightIndex], normalDir, viewDir, albedo, roughness, metalness);
    }


    //for (uint nPointLightIndex = 0; nPointLightIndex < lightsNum.z; ++nPointLightIndex)
    //{
    //    float4 diffuse;
    //    float4 specular;
    //    CalcPointLightSplit(pointLight[nPointLightIndex], worldCameraPos, pixIn.posWorld, bumpedNormalWorld, mat, diffuse, specular);
    //    rtDiffuse += diffuse;
    //    rtSpecular += specular;
    //}


    return finalColor;
}

