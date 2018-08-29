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

	auto& pWinCom = HrDirector::Instance()->GetWindowComponent();
	uint32 nTopX = pWinCom->GetWindowX();
	uint32 nTopY = pWinCom->GetWindowY();
	uint32 nWidth = HrDirector::Instance()->GetWindowComponent()->GetWindowWidth();
	uint32 nHeight = HrDirector::Instance()->GetWindowComponent()->GetWindowHeight();
	pCamera->GetViewPort()->SetViewPortAttribute(static_cast<float>(nTopX)
		, static_cast<float>(nTopY)
		, static_cast<float>(nWidth)
		, static_cast<float>(nHeight), 0);

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

HrSceneNodePtr HrSceneObjectFactory::CreateModelNode(const std::string& strName)
{
	HrMeshModelPtr pPrefabModel = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrMeshModel>(strName, true, true);
	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	return CreateMeshModelNode(pPrefabModel);
}

HrSceneNodePtr HrSceneObjectFactory::CreateMeshModelNode(HrMeshModelPtr& pMeshModel)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneNode->SetSceneObject(pSceneObj);
	pSceneNode->SetName(pMeshModel->GetFileName());

	for (size_t i = 0; i < pMeshModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSubRenderObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSubRenderObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(pMeshModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>());

		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pMeshModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSubRenderObj);
		pSceneNode->AddChild(pNode);
	}

	return pSceneNode;
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
