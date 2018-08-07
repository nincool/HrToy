
cbuffer cbPerFrame
{
	float3 camera_position;
};

cbuffer cbPerObject
{
    float4x4 world_matrix;
    float4x4 view_proj_matrix;
};

struct HrVertexInput
{
	float4 vertexPosition : POSITION;
	float4 color : COLOR;
};

struct HrVertexOutput
{
	float4 posWorldViewProj : SV_POSITION;
	float4 color : COLOR;
};

HrVertexOutput BaseVSPC(HrVertexInput vIn)
{
	HrVertexOutput vOut;

    float4x4 worldViewProjMatrix = mul(world_matrix, view_proj_matrix);
    vOut.posWorldViewProj = mul(float4(vIn.vertexPosition), worldViewProjMatrix);
	vOut.color = vIn.color;

    return vOut;
}

float4 BasePSPC(HrVertexOutput vIn) : SV_TARGET
{ 
    return vIn.color;
}

