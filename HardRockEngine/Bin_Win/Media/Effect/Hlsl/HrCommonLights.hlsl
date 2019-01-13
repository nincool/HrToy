struct DirectionLight
{
    float4 directional_light_color;
    float4 directional_light_direction;
};

struct PointLight
{
    float4 point_light_color;
    float4 point_light_range_attenuation;
    float4 point_light_position;
};

struct Material
{
    float4 material_albedo;
    float material_metalness;
    float material_roughness;
    uint material_param0;
    uint material_param1;
};

#define PI 3.141592 
#define INV_PI 0.31830988618

//---------------------------------------------------------------------
// Transforms a normal map sample to world space.
//---------------------------------------------------------------------
float3 NormalSampleToWorldSpace(float3 normalMapSample, float3 unitNormalW, float3 tangentW)
{
    // Uncompress each component from [0,1] to [-1,1].
    float3 normalT = 2.0f * normalMapSample - 1.0f;
    
    // Build orthonormal basis.
    float3 N = unitNormalW;
    float3 T = normalize(tangentW - dot(tangentW, N) * N);
    float3 B = cross(N, T);
    float3x3 TBN = float3x3(T, B, N);
    
    // Transform from tangent space to world space.
    float3 bumpedNormalW = mul(normalT, TBN);
    
    return bumpedNormalW;
}

float3 NormalSampleToWorldSpaceTBN(float3 normalmapSample, float3 tangent, float3 binormal, float3 normal)
{
    float3 normalLocal = 2.0f * normalmapSample - 1.0f;
    float3x3 TBN = float3x3(tangent, binormal, normal);

    return mul(normalLocal, TBN);

}

//				D * F * G
//    fs =  --------------
//			 4*(n*l)(n*v)
//---------------------------------------------------------------------
// PBR
//---------------------------------------------------------------------
float3 FresnelSchlick(float3 F0, float NdotV)
{
    return F0 + (float3(1.0, 1.0, 1.0) - F0) * pow(1.0 - NdotV, 5.0);
}

float NDFGGX(float NdotH, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float t = (NdotH * NdotH) * (a2 - 1.0) + 1.0;
    
    return a2 / (PI * t * t);
}

float GeometricSchlickGGX(float costheta, float roughness)
{
    float a = roughness;
    float r = a + 1.0;
    float r2 = r * r;
    float k = r2 / 8.0;

    float t = costheta * (1.0 - k) + k;

    return costheta / t;
}

float GeometricSmith(float NdotV, float NdotL, float roughness)
{
    return GeometricSchlickGGX(NdotV, roughness) * GeometricSchlickGGX(NdotL, roughness);
}

float3 DisneyDiffuse(float roughness, float LdotH, float NdotL, float NdotV, float3 baseColor)
{
    float fresnelDiffuse = 0.5 + 2 * roughness * pow(LdotH, 2);
    float fresnelL = 1 + (fresnelDiffuse - 1) * pow(1 - NdotL, 5);
    float fresnelV = 1 + (fresnelDiffuse - 1) * pow(1 - NdotV, 5);
    float3 Fd = baseColor * INV_PI * fresnelL * fresnelV;

    return Fd;
}

// Physically Based shading model: Lambetrtian diffuse BRDF + Cook-Torrance microfacet specular BRDF + IBL for ambient.

// This implementation is based on "Real Shading in Unreal Engine 4" SIGGRAPH 2013 course notes by Epic Games.
// See: http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
//void CalcDirectionLightSplit(DirectionLight directLight, float4 cameraWorldPos, float4 pixWorldPos, float3 pixNormal, Material mat, out float4 diffuse, out float4 specular)
float3 CalcPBRDirectionLight(DirectionLight directLight, float3 normalDir, float3 viewDir, float4 albedo, float roughness, float metalness)
{
    float3 halfNormal = normalize(directLight.directional_light_direction.xyz + viewDir);

    float NdotV = saturate(dot(normalDir, viewDir));
    float NdotL = saturate(dot(normalDir, directLight.directional_light_direction.xyz));
    float NdotH = saturate(dot(normalDir, halfNormal));
    float HdotV = saturate(dot(halfNormal, viewDir));

    // Calculate Fresnel term for direct lighting. 
    //F项 Fresnel F0 表面的基本反射属性 非金属材质的直接认定为 F0=0.04
    float3 F0 = lerp(float3(0.04, 0.04, 0.04), albedo.xyz, metalness);
    float3 F = FresnelSchlick(F0, HdotV);
  
    // Calculate normal distribution for specular BRDF.
    float D = NDFGGX(NdotH, roughness);

    // Calculate geometric attenuation for specular BRDF.
    float G = GeometricSmith(NdotV, NdotL, roughness);

    // Diffuse scattering happens due to light being refracted multiple times by a dielectric medium.
    // Metals on the other hand either reflect or absorb energy, so diffuse contribution is always zero.
	// To be energy conserving we must scale diffuse BRDF contribution based on Fresnel factor & metalness.
    //F项表示的就是镜面反射的比例，那么剩下的就是漫反射的比例，再考虑金属材质有没有漫反射部分的情况
    float3 kD = lerp(float3(1.0, 1.0, 1.0) - F, float3(0, 0, 0), metalness);

    // Lambert diffuse BRDF.
	// We don't scale by 1/PI for lighting & material units to be more convenient.
	// See: https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
    float3 diffuseBRDF = kD * albedo.xyz;

    // Cook-Torrance specular microfacet BRDF.
    float3 specularBRDF = (F * D * G) / (4.0 * NdotV * NdotL + 0.0001);

    return (diffuseBRDF + specularBRDF) * directLight.directional_light_color.xyz * NdotL;
}




