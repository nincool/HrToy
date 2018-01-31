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

HrSceneNodePtr HrSceneObjectFactory::CreateCamera(const std::string& strName, uint32 nTopX, uint32 nTopY, uint32 nWidth, uint32 nHeight, int nZOrder)
{
	HrCameraPtr pCamera = HrMakeSharedPtr<HrCamera>(strName);
	HrViewPortPtr pViewPort = HrMakeSharedPtr<HrViewPort>(nTopX, nTopY, nWidth, nHeight, nZOrder);
	pViewPort->SetCamera(pCamera);
	
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneObj->AddComponent(HrSceneObject::SCT_CAMERA, pCamera);

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(pCamera->GetName());
	pSceneNode->SetSceneObject(pSceneObj);

	return pSceneNode;
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

//HrLightNode* HrSceneObjectFactory::CreatePointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2)
//{
//	HrLightPtr pLight = HrCheckPointerCast<HrLight>(HrMakeSharedPtr<HrPointLight>(diffuse, specular, fRange, fAttenuation0, fAttenuation1, fAttenuation2));
//	HrLightNode* pLightNode = HR_NEW HrLightNode(pLight);
//
//	return pLightNode;
//}

HrSceneNodePtr HrSceneObjectFactory::CreatePlane(float fWidth, float fHeight)
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
	HrResourcePtr pRes = HrResourceManager::Instance()->RetriveOrLoadResource(strName, HrResource::RT_MODEL);
	HrPrefabModelPtr pPrefabModel = HrCheckPointerCast<HrPrefabModel>(pRes);
	if (pPrefabModel == nullptr)
	{
		BOOST_ASSERT(false);
		return nullptr;
	}

	return CreateSceneNode(pPrefabModel);
}

HrSceneNodePtr HrSceneObjectFactory::CreateSceneNode(HrPrefabModelPtr& pPrefabModel)
{
	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	for (size_t i = 0; i < pPrefabModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSkinnedMeshRenderablePtr pSkinnedRenderable = HrMakeSharedPtr<HrSkinnedMeshRenderable>();
		pSkinnedRenderable->AttachSubMesh(pPrefabModel->GetMesh()->GetSubMesh(i));
		pSkinnedRenderable->SetRenderEffect(HrResourceManager::Instance()->GetDefaultRenderEffect());

		HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>(pSkinnedRenderable);
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pPrefabModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSceneObj);
		pSceneNode->AddChild(pNode);
	}

	return pSceneNode;
}

