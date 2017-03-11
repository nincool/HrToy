#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrEntityNode.h"
#include "Scene/HrTransform.h"
#include "Asset/HrMaterial.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentRenderable = nullptr;
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

void HrRenderFrameParameters::SetCurrentScene(const HrScenePtr& pScene)
{
	m_pCurrentScene = pScene;

	//环境光
	m_ambientColor = m_pCurrentScene->GetAmbientColor();

	//直线光
	if (m_pCurrentScene->IsLightsDirty(HrLight::LT_DIRECTIONAL))
	{
		m_pCurrentScene->GetDirectionalLightsParam(m_vecDirectionalDirections, m_vecDirectionalDiffuseColor, m_vecDirectionalSpecularColor);
		m_lightsNum[0] = m_vecDirectionalDirections.size();
	}
}

void HrRenderFrameParameters::SetCurrentRenderable(const HrRenderable* rend)
{
	m_pCurrentRenderable = rend;

	m_bWorldMatrixDirty = true;
	m_bWorldViewProjMatrixDirty = true;
}

void HrRenderFrameParameters::SetCurrentCamera(HrCamera* pCamera)
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

void HrRenderFrameParameters::SetCurrentMaterial(const HrMaterial* pMaterial)
{
	m_pCurrentMaterial = pMaterial;
	BOOST_ASSERT(m_pCurrentMaterial);
}

const Matrix4& HrRenderFrameParameters::GetWorldMatrix()
{
	if (m_bWorldMatrixDirty)
	{
		m_bWorldMatrixDirty = false;
		m_worldMatrix = m_pCurrentRenderable->GetSceneNode()->GetTransform()->GetWorldMatrix();
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
		m_worldViewProjMatrix = m_worldMatrix * m_pCurrentCamera->GetViewProjMatrix();
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
		m_cameraPosition = m_pCurrentCamera->GetAttachCameraNode()->GetTransform()->GetWorldPosition();
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

const float4& HrRenderFrameParameters::GetAmbientColor()
{
	return m_ambientColor;
}

const int3& HrRenderFrameParameters::GetLightsNum()
{
	return m_lightsNum;
}

const std::vector<float3>& HrRenderFrameParameters::GetDirectionalLightDirections()
{
	return m_vecDirectionalDirections;
}

const std::vector<float4>& HrRenderFrameParameters::GetDirectionalLightDiffuseColors()
{
	return m_vecDirectionalDiffuseColor;
}

const std::vector<float4>& HrRenderFrameParameters::GetDirectionalLightSpecularColors()
{
	return m_vecDirectionalSpecularColor;
}

