
struct HrVertexInputP
{
	float3 vertexPosition : POSITION;
};

struct HrVertexInputPC
{
	float3 vertexPosition : POSITION;
	float3 color : COLOR;
};

struct HrVertexInputPN
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
};

struct HrVertexInputPNC
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
	float2 vertexCoord : TEXCOORD0;
};

struct HrVertexInputPTBNC
{
	float3 vertexPosition : POSITION;
	float3 vertexTangent : TANGENT;
	float3 vertexBinormal : BINORMAL;
	float3 vertexNormal : NORMAL;
	float2 vertexCoord : TEXCOORD0;
};

