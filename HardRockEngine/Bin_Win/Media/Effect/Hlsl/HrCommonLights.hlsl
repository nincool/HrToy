struct DirectionLight
{
    float4 diffuse_light_color;
    float4 specular_light_color;
    float4 light_direction;
};

struct PointLight
{
    float4 point_light_diffuse_color;
    float4 point_light_specular_color;
    float4 point_light_range_attenuation;
    float4 point_light_position;
};

struct Material
{
    float glossiness_material;

    float4 ambient_material_color;
    float4 diffuse_material_color;
    float4 specular_material_color;
};

float4 CalcDirectionLight(DirectionLight directLight, float4 cameraWorldPos, float4 pixWorldPos, float3 pixNormal, Material mat)
{
    //Phong diffuse
    //float fNDotL = saturate(dot(normalize(-directLight.light_direction.xyz), pixNormal)); 
	float fNDotL = dot(normalize(-directLight.light_direction.xyz), pixNormal) * 0.5 + 0.5;
    float4 finalColor = directLight.diffuse_light_color * saturate(fNDotL) * mat.diffuse_material_color;

    //Blinn specular
    float3 toCameraDir = normalize(cameraWorldPos - pixWorldPos).xyz;
    float3 halfWay = normalize(toCameraDir + -directLight.light_direction.xyz);
    //float fNDotH = saturate(dot(halfWay, pixNormal));
	float fNDotH = dot(halfWay, pixNormal) * 0.5 + 0.5;
    finalColor += directLight.specular_light_color * pow(fNDotH, mat.glossiness_material) * mat.specular_material_color;

    return finalColor;
}

float4 CalcPointLight(PointLight pointLight, float4 cameraWorldPos, float4 pixWorldPos, float3 pixNormal, Material mat)
{
    float3 toLightDir = (pointLight.point_light_position - pixWorldPos).xyz;
    float3 toCameraDir = (cameraWorldPos - pixWorldPos).xyz;
    float fDistToLight = length(toLightDir);

    //phong diffuse
    toLightDir /= fDistToLight; //Normalize
    //float fNDotL = saturate(dot(toLightDir, pixNormal));
    float fNDotL = dot(toLightDir, pixNormal) * 0.5 + 0.5;
    float4 finalColor = pointLight.point_light_diffuse_color * mat.diffuse_material_color * fNDotL;

    //Blinn specular
    toCameraDir = normalize(toCameraDir);
    float3 halfWay = normalize(toCameraDir + toLightDir);
    float fNDotH = saturate(dot(halfWay, pixNormal));
    finalColor += pointLight.point_light_specular_color * pow(fNDotH, mat.glossiness_material) * mat.specular_material_color;

    //Attenuation
    //float fDistToLightNorm = 1.0 - saturate(fDistToLight / pointLight.point_light_range_attenuation.w);
    //float fAttn = fDistToLightNorm * fDistToLightNorm;
    float fAttn = 1 / (pointLight.point_light_range_attenuation.x + pointLight.point_light_range_attenuation.y * fDistToLight + pointLight.point_light_range_attenuation.z * fDistToLight * fDistToLight);
    finalColor *= fAttn;

    return finalColor;

}




