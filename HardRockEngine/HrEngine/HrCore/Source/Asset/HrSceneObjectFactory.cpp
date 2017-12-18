#include "HrCore/Include/Asset/HrSceneObjectFactory.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrPrefabModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Render/HrLight.h"
#include "HrCore/Include/Scene/HrEntityNode.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;


HrSceneObjectFactory::HrSceneObjectFactory()
{
	m_pGeometryFactory = HrMakeSharedPtr<HrGeometryFactory>();
}

HrSceneObjectFactory::~HrSceneObjectFactory()
{
}

HrCameraNode* HrSceneObjectFactory::CreateCamera()
{
	return CreateCamera(0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
}

HrCameraNode* HrSceneObjectFactory::CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrCamera* pCamera = HR_NEW HrCamera();
	HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	HrCameraNode* pCameraNode = HR_NEW HrCameraNode(pViewPort);

	return pCameraNode;
}

HrLightNode* HrSceneObjectFactory::CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular)
{
	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrDirectionalLight>(direction, diffuse, specular));
	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);

	return pLightNode;
}

HrLightNode* HrSceneObjectFactory::CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
{
	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrPointLight>(diffuse, specular, fRange, fAttenuation0, fAttenuation1, fAttenuation2));
	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);

	return pLightNode;
}

HrSceneNode* HrSceneObjectFactory::CreatePlane(float fWidth, float fHeight)
{
	return m_pGeometryFactory->CreatePlane(fWidth, fHeight);
}

HrSceneNode* HrSceneObjectFactory::CreateBox(float fLength)
{
	return m_pGeometryFactory->CreateBox(fLength);
}

HrSceneNode* HrSceneObjectFactory::CreateSkyBox()
{
	return m_pGeometryFactory->CreateSkyBox();
}

HrSceneNode* HrSceneObjectFactory::CreateModel(const std::string& strName)
{
	HrResource* pRes = HrResourceManager::Instance()->GetOrLoadResource(strName, HrResource::RT_MODEL);
	HrPrefabModel* pPrefabModel = static_cast<HrPrefabModel*>(pRes);

	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	HrSceneNode* pSceneNode = HR_NEW HrSceneNode();
	for (size_t i = 0; i < pPrefabModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSkinnedMeshRenderable* pSkinRenderable = HR_NEW HrSkinnedMeshRenderable();
		pSkinRenderable->AttachSubMesh(pPrefabModel->GetMesh()->GetSubMesh(i));
		HrSceneNode* pChildNode = HR_NEW HrSceneNode(pPrefabModel->GetMesh()->GetSubMesh(i)->GetName(), pSkinRenderable);
		pSceneNode->AddChild(pChildNode);
	}

	return pSceneNode;
}

