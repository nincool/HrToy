

struct DirectionLight
{
    float4 fAmbient;
    float4 fDiffuse;
    float4 fSpecular;
    float3 fDirection;
};

struct Material
{
    float4 fAmbient;
    float4 fDiffuse;
    float4 fSpecular;
    float4 fReflect;
};


void ComputeDirectionLight(Material mat, DirectionLight directLight, float3 normal, float3 toEye, out float4 fAmbient, out float4 fDiffuse, out float4 fSpec)
{
    fAmbient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    fDiffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    fSpec = float4(0.0f, 0.0f, 0.0f, 0.0f);


    float3 fLightVec = -directLight.fDirection;
    
    fAmbient = mat.fAmbient * directLight.fAmbient;

    float fDiffuseFactor = dot(fLightVec, normal);

    fDiffuse = fDiffuseFactor * mat.fDiffuse * directLight.fDiffuse;
}








