#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObject.h"
#include "Asset/HrMaterial.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentMaterial = nullptr;
	m_pCurrentCamera = nullptr;

	m_bWorldMatrixDirty = true;
	m_bInverseWorldMatrixDirty = true;
	m_bInverseTransposeWorldMatrix = true;
	m_bWorldViewProjMatrixDirty = true;

	m_worldMatrix = Matrix4::Identity();
}

HrRenderFrameParameters::~HrRenderFrameParameters()
{
}


void HrRenderFrameParameters::SetCurrentSceneNode(const HrSceneNodePtr& pSceneNode)
{
	m_pCurrentSceneNode = pSceneNode;
	m_pCurrentMaterial = pSceneNode->GetSceneObject()->GetRenderable()->GetMaterial();

	//todo
	m_bWorldMatrixDirty = true;
	m_bWorldViewProjMatrixDirty = true;
}


void HrRenderFrameParameters::SetLightsData(const HrSceneLightDataPtr& pLightData)
{
	m_pLightsData = pLightData;
}

void HrRenderFrameParameters::SetCurrentCamera(const HrCameraPtr& pCamera)
{
	if (m_pCurrentCamera != pCamera)
	{
		m_pCurrentCamera = pCamera;
		m_bCameraDirty = true;
		m_bWorldViewProjMatrixDirty = true;
	}
	else if (m_pCurrentCamera->ViewProjDirty())
	{
		m_bCameraDirty = true;
		m_bWorldViewProjMatrixDirty = true;
	}
}

void HrRenderFrameParameters::SetCurrentMaterial(const HrMaterialPtr& pMaterial)
{
	m_pCurrentMaterial = pMaterial;
	BOOST_ASSERT(m_pCurrentMaterial);
}

const Matrix4& HrRenderFrameParameters::GetWorldMatrix()
{
	if (m_bWorldMatrixDirty)
	{
		m_bWorldMatrixDirty = false;
		m_worldMatrix = m_pCurrentSceneNode->GetTransform()->GetWorldMatrix();
	}
	return m_worldMatrix;
}

const Matrix4& HrRenderFrameParameters::GetInverseWroldMatrix()
{
	if (m_bInverseWorldMatrixDirty)
	{
		m_inverseWorldMatrix = HrMath::Inverse(GetWorldMatrix());
	}
	return m_inverseWorldMatrix;
}

const Matrix4& HrRenderFrameParameters::GetViewProjMatrix() const
{
	return m_pCurrentCamera->GetViewProjMatrix();
}

const Matrix4& HrRenderFrameParameters::GetWorldViewProjMatrix()
{
	if (m_bWorldViewProjMatrixDirty)
	{
		m_worldViewProjMatrix = GetWorldMatrix() * m_pCurrentCamera->GetViewProjMatrix();
		m_bWorldViewProjMatrixDirty = false;
	}
	
	return m_worldViewProjMatrix;
}

const Matrix4& HrRenderFrameParameters::GetInverseTransposeWorldMatrix()
{
	if (m_bInverseTransposeWorldMatrix)
	{
		m_inverseTransposeWorldMatrix = HrMath::Transpose(GetInverseWroldMatrix());
	}
	return m_inverseTransposeWorldMatrix;
}

float HrRenderFrameParameters::GetMaterialGlossiness() const
{
	return m_pCurrentMaterial->GetGlossiness();
}

float4 HrRenderFrameParameters::GetMaterialAmbient() const
{
	BOOST_ASSERT(m_pCurrentMaterial);
	return m_pCurrentMaterial->GetAmbient();
}

float4 HrRenderFrameParameters::GetMaterialDiffuse() const
{
	BOOST_ASSERT(m_pCurrentMaterial);
	return m_pCurrentMaterial->GetDiffuse();
}

float4 HrRenderFrameParameters::GetMaterialSpecular() const
{
	BOOST_ASSERT(m_pCurrentMaterial);
	return m_pCurrentMaterial->GetSpecular();
}

float4 HrRenderFrameParameters::GetMaterialEmissive() const
{
	BOOST_ASSERT(m_pCurrentMaterial);
	return m_pCurrentMaterial->GetEmissive();
}

float HrRenderFrameParameters::GetMaterialOpacity() const
{
	BOOST_ASSERT(m_pCurrentMaterial);
	return m_pCurrentMaterial->GetOpacity();
}

const float3& HrRenderFrameParameters::GetCameraPosition()
{
	if (m_bCameraDirty)
	{
		m_cameraPosition = m_pCurrentCamera->GetEyePos();
		m_bCameraDirty = false;
	}
	return m_cameraPosition;
}

void HrRenderFrameParameters::SetFogParam(float4& fogColor, float fogStart, float fogRange)
{
	m_fogColor = fogColor;
	m_fogStart = fogStart;
	m_fogRange = fogRange;
}

const void HrRenderFrameParameters::GetFogParam(float4& fogColor, float& fogStart, float& fogRange)
{
	fogColor = m_fogColor;
	fogStart = m_fogStart;
	fogRange = m_fogRange;
}

const float4 HrRenderFrameParameters::GetAmbientColor()
{
	return m_pLightsData->GetLight(HrLight::LT_AMBIENT, 0)->GetDiffuse().Value();
}

const uint4 HrRenderFrameParameters::GetLightsNum()
{
	return uint4(m_pLightsData->GetLightsNum(HrLight::LT_AMBIENT), m_pLightsData->GetLightsNum(HrLight::LT_POINT), m_pLightsData->GetLightsNum(HrLight::LT_DIRECTIONAL), 0);
}

const int HrRenderFrameParameters::GetLightNum(HrLight::EnumLightType lightType)
{
	return m_pLightsData->GetLightsNum(lightType);
}

const float4 HrRenderFrameParameters::GetDirectionalLightDirection(int nLightIndex)
{
	const Vector3& v3Direction = m_pLightsData->GetLight(HrLight::LT_DIRECTIONAL, nLightIndex)->GetDirection();
	return float4(v3Direction.x(), v3Direction.y(), v3Direction.z(), 0.0f);
}

const float4 HrRenderFrameParameters::GetDirectionalLightDiffuseColor(int nLightIndex)
{
	return m_pLightsData->GetLight(HrLight::LT_DIRECTIONAL, nLightIndex)->GetDiffuse().Value();
}

const float4 HrRenderFrameParameters::GetDirectionalLightSpecularColor(int nLightIndex)
{
	return m_pLightsData->GetLight(HrLight::LT_DIRECTIONAL, nLightIndex)->GetSpecular().Value();
}

const float4 HrRenderFrameParameters::GetPointLightDiffuseColor(int nLightIndex)
{
	return m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetDiffuse().Value();
}

const float4 HrRenderFrameParameters::GetPointLightSpecularColor(int nLightIndex)
{
	return m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetSpecular().Value();
}

const float4 HrRenderFrameParameters::GetPointLightPosition(int nLightIndex)
{
	const Vector3& v3Position = m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetPosition();
	return float4(v3Position.x(), v3Position.y(), v3Position.z(), 0.0);
}

const float4 HrRenderFrameParameters::GetPointLightAttenuation(int nLightIndex)
{
	return float4(m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetAttenuation0()
		, m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetAttenuation1()
		, m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetAttenuation2()
		, m_pLightsData->GetLight(HrLight::LT_POINT, nLightIndex)->GetAttenuationRange());
}

