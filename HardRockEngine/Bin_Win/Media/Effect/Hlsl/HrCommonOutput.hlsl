
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
	float3 pixWorldNormal : NORMAL;
	float2 uv : TEXCOORD;
};

