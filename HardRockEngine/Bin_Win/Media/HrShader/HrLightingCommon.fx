
struct DirectionLight
{

    float4 diffuse_light_color[4];
    float4 specular_light_color[4];
    float3 light_direction[4];
};

struct PointLight
{
    float4 point_light_diffuse_color[4];
    float4 point_light_specular_color[4];
    float3 point_light_position[4];
    float4 point_light_range_attenuation[4];
};

struct Material
{
    float4 ambient_material_color;
    float4 diffuse_material_color;
    float4 specular_material_color;
    float4 reflect_material_color;
};






