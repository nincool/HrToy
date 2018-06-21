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






