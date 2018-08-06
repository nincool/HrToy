#include "Asset/HrSceneObjectFactory.h"
#include "Asset/HrMeshModel.h"
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
#include "Kernel/HrCoreComponentWin.h"

using namespace Hr;


HrSceneObjectFactory::HrSceneObjectFactory()
{
}

HrSceneObjectFactory::~HrSceneObjectFactory()
{
}

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName)
{
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	pSceneNode->SetSceneObject(pSceneObj);
	HrCameraComponentPtr pCamera = pSceneObj->AddComponent<HrCameraComponet>();

	float fWidth = HrDirector::Instance()->GetWindowComponent()->GetWindowWidth();
	float fHeight = HrDirector::Instance()->GetWindowComponent()->GetWindowHeight();
	pCamera->GetViewPort()->SetViewPortAttribute(0.0f, 0.0f, fWidth, fHeight, 0);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName, float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder)
{
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	pSceneNode->SetSceneObject(pSceneObj);
	HrCameraComponentPtr pCamera = pSceneObj->AddComponent<HrCameraComponet>();
	pCamera->GetViewPort()->SetViewPortAttribute(fTopX, fTopY, fWidth, fHeight, nZOrder);

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
	HrModelPtr pPrefabModel = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrModel>(strName, true, true);
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
	pSceneNode->SetName(pModel->GetFileName());

	for (size_t i = 0; i < pModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSubRenderObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSubRenderObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(pModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>());
		
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSubRenderObj);
		pSceneNode->AddChild(pNode);
	}

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType)
{
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	HrLightComponentPtr pLight = HrMakeSharedPtr<HrLightComponent>(strName, pSceneObj, lightType);
	pSceneObj->AddComponent(pLight);

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	pSceneNode->SetSceneObject(pSceneObj);

	return pSceneNode; 
}

HrSceneNodePtr HrSceneObjectFactory::CreateGridPlan()
{
	//the name of grid is default
	//const std::string strGridMeshMode = 
	HrMeshModelPtr pMeshModel = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrMeshModel>("BuildIn_Grid", true, false);
	if (!pMeshModel)
	{
		return nullptr;
	}
	else
	{
		pMeshModel->Load();
	}

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneNode->SetSceneObject(pSceneObj);
	pSceneNode->SetName(pMeshModel->GetFileName());

	for (size_t i = 0; i < pMeshModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(pMeshModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>());

		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pMeshModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSceneObj);
		pSceneNode->AddChild(pNode);
	}

	return pSceneNode;
}

