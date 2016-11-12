
cbuffer PerFrame
{
	float4x4	worldviewproj_matrix;
};

struct VertexIn
{
	float3	pos 	: POSITION;
	float4	color 	: COLOR;
};

struct VertexOut
{
	float4	posH	: SV_POSITION;
	float4	color	: COLOR;
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;
	vout.posH = mul(float4(vin.pos,1.f),worldviewproj_matrix);
	vout.color = vin.color;
	
	return vout;
}

float4 PS_Main(VertexOut pin):SV_TARGET
{
	return pin.color;
}

