#include "Light.fx"

//��Ե��������Effectȫ�ֱ���
cbuffer PerObject
{
	float4x4	g_worldViewProj;		//���硢�ӽǡ�ͶӰ�任
	float4x4	g_worldInvTranspose;	//����任���桢ת�þ���
	float4x4	g_world;				//����任
};

//���ÿһ֡��Effectȫ�ֱ���
cbuffer PerFrame
{
	SpotLight	g_spotLight;
	Material	g_material;
	float3		g_eyePos;
};

//����
Texture2D g_tex;

//���ù���
SamplerState samTex
{
	Filter = MIN_MAG_MIP_LINEAR;
};

//���붥����Ϣ��λ�����ꡢ���ߡ���������
struct VertexIn
{
	float3	pos:	POSITION;
	float3	normal:	NORMAL;
	float2	tex:	TEXCOORD;
};

//���������Ϣ
struct VertexOut
{
	float4	posH:	SV_POSITION;	//ͶӰ������
	float3	pos:	POSITION;		//����任������
	float3	normal:	NORMAL;			//����任����
	float2	tex:	TEXCOORD;		//��������
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	vout.posH = mul(float4(vin.pos,1.f),g_worldViewProj);
	vout.pos = mul(float4(vin.pos,1.f),g_world).xyz;
	vout.normal = mul(vin.normal,(float3x3)g_worldInvTranspose);
	vout.tex = vin.tex;

	return vout;
}

float4 PS(VertexOut pin, uniform bool useLight): SV_TARGET
{
	float4 ambient = {1.f,1.f,1.f,1.f};
	float4 diffuse = {0.f,0.f,0.f,0.f};
	float4 spec = {0.f,0.f,0.f,0.f};

	//���ʹ�ù���
	if(useLight)
	{
		float3 normal = normalize(pin.normal);
		float3 toEye = normalize(g_eyePos - pin.pos);

		ComputeSpotLight(g_material,g_spotLight,normal,pin.pos,toEye,ambient,diffuse,spec);
	}

	float4 texColor = g_tex.Sample(samTex,pin.tex);
	//����*(������+������⣩+ȫ����⣬����������ɫ
	float4 finalColor = texColor * (ambient+diffuse) + spec;

	return finalColor;
}

//ʹ�ù��յ�technique
technique11 TexLight
{
	pass P0
	{
		SetVertexShader( CompileShader(vs_5_0,VS()) );
		SetPixelShader( CompileShader(ps_5_0,PS(true)) );
	}
}

//��ʹ�ù��յ�technique
technique11 Tex
{
	pass P0
	{
		SetVertexShader( CompileShader(vs_5_0,VS()) );
		SetPixelShader( CompileShader(ps_5_0,PS(false)) );
	}
}