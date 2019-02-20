#include "Asset/HrSceneObjectFactory.h"
#include "Asset/HrMeshModel.h"
#include "Asset/HrResourceManager.h"
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
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrWindowModule.h"

using namespace Hr;


HrSceneObjectFactory::HrSceneObjectFactory()
{
}

HrSceneObjectFactory::~HrSceneObjectFactory()
{
}

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	HrCameraComponentPtr pCamera = pSceneNode->GetSceneObject()->AddComponent<HrCameraComponet>();

	auto& pWinCom = HrDirector::Instance()->GetWindowModule();
	uint32 nTopX = pWinCom->GetWindowX();
	uint32 nTopY = pWinCom->GetWindowY();
	uint32 nWidth = HrDirector::Instance()->GetWindowModule()->GetWindowWidth();
	uint32 nHeight = HrDirector::Instance()->GetWindowModule()->GetWindowHeight();
	pCamera->GetViewPort()->SetViewPortAttribute(static_cast<float>(nTopX)
		, static_cast<float>(nTopY)
		, static_cast<float>(nWidth)
		, static_cast<float>(nHeight), 0);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName, float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	HrCameraComponentPtr pCamera = pSceneNode->GetSceneObject()->AddComponent<HrCameraComponet>();
	pCamera->GetViewPort()->SetViewPortAttribute(fTopX, fTopY, fWidth, fHeight, nZOrder);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateModelNode(const std::string& strName)
{
	HrMeshModelPtr pPrefabModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(strName, true, true);
	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	return CreateMeshModelNode(pPrefabModel);
}

HrSceneNodePtr HrSceneObjectFactory::CreateMeshModelNode(HrMeshModelPtr& pMeshModel)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(pMeshModel->GetFileName());
	BuildupSceneNodeWithMesh(pMeshModel, pSceneNode);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateLightNode(const std::string& strName, HrLight::EnumLightType lightType)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
	HrLightComponentPtr pLight = HrMakeSharedPtr<HrLightComponent>(strName, pSceneNode->GetSceneObject().get(), lightType);
	pSceneNode->GetSceneObject()->AddComponent(pLight);

	return pSceneNode; 
}

HrSceneNodePtr HrSceneObjectFactory::CreateGridPlan()
{
	//the name of grid is default
	std::shared_ptr< HrMeshModelGrid> pMeshModelGrid = HrMakeSharedPtr<HrMeshModelGrid>(100.0f, 30.0f);
	pMeshModelGrid->DeclareResource("Buildin_Grid", "Buildin_Grid");
	if (!pMeshModelGrid)
	{
		return nullptr;
	}
	else
	{
		pMeshModelGrid->Load();
	}

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	pSceneNode->SetName(pMeshModelGrid->GetFileName());
	BuildupSceneNodeWithMesh(pMeshModelGrid, pSceneNode);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight)
{
	HrSceneNodePtr pSceneNode = CreateSceneNode(strName);
	std::shared_ptr<HrMeshModelQuadP> pMeshModel = HrMakeSharedPtr<HrMeshModelQuadP>(fWidth, fHeight);
	BuildupSceneNodeWithMesh(pMeshModel, pSceneNode);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateQuadNodePN(const std::string& strName, float fWidth, float fHeight)
{
	HrSceneNodePtr pSceneNode = CreateSceneNode(strName);
	std::shared_ptr<HrMeshModelQuadPN> pMeshModel = HrMakeSharedPtr<HrMeshModelQuadPN>(fWidth, fHeight);
	BuildupSceneNodeWithMesh(pMeshModel, pSceneNode);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::CreateSceneNode(const std::string& strName)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);

	return pSceneNode;
}

HrSceneNodePtr HrSceneObjectFactory::BuildupSceneNodeWithMesh(const HrMeshModelPtr& pMeshModel, const HrSceneNodePtr& pSceneNode)
{
	for (size_t i = 0; i < pMeshModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		auto& pSubMesh = pMeshModel->GetMesh()->GetSubMesh(i);
		HrSceneNodePtr pSubMeshNode = CreateSceneNode(pSubMesh->GetName());
		HrRenderableComponentPtr pRenderableCom = pSubMeshNode->GetSceneObject()->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>(pSubMesh);
		pRenderableCom->SetRenderable(pRenderable);

		pSceneNode->AddChild(pSubMeshNode);
	}

	return pSceneNode;
}

