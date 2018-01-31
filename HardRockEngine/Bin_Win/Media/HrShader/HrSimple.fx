
cbuffer PerFrame
{
	float4x4	world_view_proj_matrix;
};

struct VertexIn
{
	float3	pos 	: POSITION;
	float3  normal  : NORMAL;
	float2  uv      : TEXCOORD;
};

struct VertexOut
{
	float4	posH	: SV_POSITION;
	float4	color	: COLOR;
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;
	vout.posH = mul(float4(vin.pos,1.f),world_view_proj_matrix);
	vout.color = float4(1.0, 1.0, 1.0, 1.0);
	
	return vout;
}

float4 PS_Main(VertexOut pin):SV_TARGET
{
	return pin.color;
}

