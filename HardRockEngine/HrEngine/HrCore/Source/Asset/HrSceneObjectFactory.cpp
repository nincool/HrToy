#include "Asset/HrSceneObjectFactory.h"
#include "Asset/HrGeometryFactory.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Render/HrViewPort.h"
#include "Render/HrLight.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentResource.h"

using namespace Hr;


HrSceneObjectFactory::HrSceneObjectFactory()
{
	//m_pGeometryFactory = HrMakeSharedPtr<HrGeometryFactory>();
}

HrSceneObjectFactory::~HrSceneObjectFactory()
{
}

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName, float nTopX, float nTopY, float nWidth, float nHeight, int nZOrder)
{
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	HrCameraComponentPtr pCamera = HrMakeSharedPtr<HrCameraComponet>(strName, pSceneObj);
	HrViewPortPtr pViewPort = HrMakeSharedPtr<HrViewPort>(nTopX, nTopY, nWidth, nHeight, nZOrder);
	pViewPort->SetCamera(pCamera->GetCamera());
	pSceneObj->AddComponent(pCamera);

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(pCamera->GetName());
	pSceneNode->SetSceneObject(pSceneObj);

	return pSceneNode;
}

//HrLightNodePtr HrSceneObjectFactory::CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular)
//{
//	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrDirectionalLight>(direction, diffuse, specular));
//	HrLightNodePtr pLightNode = HrMakeSharedPtr<HrLightNode>(pLight);
//
//	return pLightNode;
//}

//HrLightNode* HrSceneObjectFactory::CreateDirectionalLight(const Vector3& direction, const HrColor& diffuse, const HrColor& specular)
//{
//	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrDirectionalLight>(direction, diffuse, specular));
//	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);
//
//	return pLightNode;
//}

//HrLightNode* HrSceneObjectFactory::CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
//{
//	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrPointLight>(diffuse, specular, fRange, fAttenuation0, fAttenuation1, fAttenuation2));
//	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);
//
//	return pLightNode;
//}

//HrSceneNodePtr HrSceneObjectFactory::CreatePlane(float fWidth, float fHeight)
//{
//	return m_pGeometryFactory->CreatePlane(fWidth, fHeight);
//}
//
//HrSceneNode* HrSceneObjectFactory::CreateBox(float fLength)
//{
//	return m_pGeometryFactory->CreateBox(fLength);
//}
//
//HrSceneNode* HrSceneObjectFactory::CreateSkyBox()
//{
//	return m_pGeometryFactory->CreateSkyBox();
//}

HrSceneNodePtr HrSceneObjectFactory::CreateModelNode(const std::string& strName)
{
	HrModelPtr pPrefabModel = HrDirector::Instance()->GetResCoreComponent()->RetriveResource<HrModel>(strName, true, true);
	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	return CreateSceneNode(pPrefabModel);
}

HrSceneNodePtr HrSceneObjectFactory::CreateSceneNode(HrModelPtr& pModel)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneNode->SetSceneObject(pSceneObj);

	for (size_t i = 0; i < pModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(pModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResCoreComponent()->RetriveResource<HrRenderEffect>());
		
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSceneObj);
		pSceneNode->AddChild(pNode);
	}

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType)
{
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	HrLightComponentPtr pLight = HrMakeSharedPtr<HrLightComponent>(strName, pSceneObj, lightType);
	pSceneObj->AddComponent(pLight);

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	pSceneNode->SetSceneObject(pSceneObj);

	return pSceneNode;
}

