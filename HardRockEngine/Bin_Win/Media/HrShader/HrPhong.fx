#include "HrLightingCommon.fx"

cbuffer cbPerFrame
{
    uint3 lightsNum;
    uint shininess;
    float4 ambientLightColor;
    DirectionLight directLight;
    PointLight pointLight;
};

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 world_view_proj_matrix;
    float4x4 inverse_transpose_world_matrix;
    Material mat;

    float3 camera_position;
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
    float3 worldCameraPos = camera_position;
    float3 posWorldTranslate = mul(float4(vIn.vertexPosition, 1.0f), world_matrix).xyz;
    float3 viewDir = normalize(worldCameraPos - posWorldTranslate);


    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    rtAmbient = mat.ambient_material_color * ambientLightColor;

    for (uint i = 0; i < lightsNum[0]; ++i)
    {
        float3 lightDir = normalize(-directLight.light_direction[i]);
        float fDiffuseFactor = max(0, dot(lightDir, normalDirection));
        rtDiffuse += fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color[i];
 

        float3 reflectSpecularDir = 2 * lightDir * normalDirection * normalDirection - lightDir;
        rtSpecular += mat.specular_material_color * directLight.specular_light_color[i] * pow(max(dot(viewDir, reflectSpecularDir), 0), 30);
    }
    vOut.pixelColor = rtAmbient + rtDiffuse + rtSpecular;


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
    float3 worldCameraPos = camera_position;
    float3 posWorldTranslate = mul(float4(vIn.vertexPosition, 1.0f), world_matrix).xyz;
    float3 viewDir = normalize(worldCameraPos - posWorldTranslate);


    float4 rtAmbient = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtDiffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
    float4 rtSpecular = { 0.0f, 0.0f, 0.0f, 1.0f };

    rtAmbient += mat.ambient_material_color * ambientLightColor;

    //平行光
    for (uint i = 0; i < lightsNum[0]; ++i)
    {
        float3 lightDir = normalize(-directLight.light_direction[i]);
        float fDiffuseFactor = max(0, dot(lightDir, normalDirection));
        rtDiffuse += fDiffuseFactor * mat.diffuse_material_color * directLight.diffuse_light_color[i];
 
        float3 halfViewLight = normalize(lightDir + viewDir);
        rtSpecular += mat.specular_material_color * directLight.specular_light_color[i] * pow(max(dot(normalDirection, halfViewLight), 0), 5);

    }

    //点光源
    for (uint i = 0; i < lightsNum[1]; ++i)
    {
        //定点到光源的向量
        float3 dirVertex2Light = pointLight.point_light_position[i] - posWorldTranslate;
        float fDistance = length(dirVertex2Light);
        dirVertex2Light = normalize(dirVertex2Light);
        if (fDistance < pointLight.point_light_range_attenuation[i].x)
        {
            //求漫反射
            float fDiffuseFactor = max(0, dot(dirVertex2Light, normalDirection));

            float fAttenuation = 1.0f / (pointLight.point_light_range_attenuation[i].y
             + pointLight.point_light_range_attenuation[i].z * fDistance
            + pointLight.point_light_range_attenuation[i].w * pow(fDistance, 2));


            rtDiffuse += mat.diffuse_material_color * pointLight.point_light_diffuse_color[i] * fDiffuseFactor * fAttenuation;
            
            //镜面反射
            float3 halfViewLight = normalize(dirVertex2Light + viewDir);
            rtSpecular += mat.specular_material_color * pointLight.point_light_specular_color[i] * pow(max(dot(normalDirection, halfViewLight), 0), 5) * fAttenuation;
        }
    }

    vOut.pixelColor = rtAmbient + rtDiffuse + rtSpecular;
    vOut.pixelColor.w = 1;

    return vOut;
}

float4 Pass1_PS_Main(VertexOut pixIn) : SV_TARGET
{
    return pixIn.pixelColor;
}





