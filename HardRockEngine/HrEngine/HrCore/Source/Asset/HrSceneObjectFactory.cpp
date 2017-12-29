#include "Asset/HrSceneObjectFactory.h"
#include "Asset/HrGeometryFactory.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrPrefabModel.h"
#include "Asset/HrMesh.h"
#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"
#include "Render/HrSkinnedMeshRenderable.h"
#include "Render/HrLight.h"
#include "Scene/HrEntityNode.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
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

HrCameraNodePtr HrSceneObjectFactory::CreateCamera()
{
	return CreateCamera(0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
}

HrCameraNodePtr HrSceneObjectFactory::CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrCameraPtr pCamera = HrMakeSharedPtr<HrCamera>();
	HrViewPortPtr pViewPort = HrMakeSharedPtr<HrViewPort>(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	HrCameraNodePtr pCameraNode = HrMakeSharedPtr<HrCameraNode>(pViewPort);

	//HrCamera* pCamera = HR_NEW HrCamera();
	//HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	//HrCameraNode* pCameraNode = HR_NEW HrCameraNode(pViewPort);

	return pCameraNode;
}

HrLightNodePtr HrSceneObjectFactory::CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular)
{
	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrDirectionalLight>(direction, diffuse, specular));
	HrLightNodePtr pLightNode = HrMakeSharedPtr<HrLightNode>(pLight);

	return pLightNode;
}

//HrLightNode* HrSceneObjectFactory::CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular)
//{
//	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrDirectionalLight>(direction, diffuse, specular));
//	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);
//
//	return pLightNode;
//}

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

HrSceneNodePtr HrSceneObjectFactory::CreateModel(const std::string& strName)
{
	//todo shared
	HrResource* pRes = HrResourceManager::Instance()->GetOrLoadResource(strName, HrResource::RT_MODEL);
	HrPrefabModel* pPrefabModel = static_cast<HrPrefabModel*>(pRes);
	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	std::shared_ptr<HrPrefabModel> pSharedPrefabModel(pPrefabModel);
	
	return CreateSceneNode(pSharedPrefabModel);
}

HrSceneNodePtr HrSceneObjectFactory::CreateSceneNode(HrPrefabModelPtr& pPrefabModel)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	for (size_t i = 0; i < pPrefabModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSkinnedMeshRenderablePtr pSkinnedRenderable = HrMakeSharedPtr<HrSkinnedMeshRenderable>();
		pSkinnedRenderable->AttachSubMesh(pPrefabModel->GetMesh()->GetSubMesh(i));
		HrSceneObjectPtr pSceneObject = HrMakeSharedPtr<HrSceneObject>(pPrefabModel->GetMesh()->GetSubMesh(i)->GetName(), pSkinnedRenderable);
		HrSceneNodePtr pChildNode = HrMakeSharedPtr<HrSceneNode>(pSceneObject->GetName(), pSceneObject);
		pSceneNode->AddChild(pChildNode);
	}

	return pSceneNode;
}

