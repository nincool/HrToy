#include "Asset/HrGeometryFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Asset/HrGeometryBox.h"
#include "Scene/HrSceneNode.h"

using namespace Hr;

HrGeometryFactoryPtr HrGeometryFactory::m_s_pUniqueFactory;

HrGeometryFactory::HrGeometryFactory()
{

}

HrGeometryFactory::~HrGeometryFactory()
{
}

HrGeometryFactory& HrGeometryFactory::GetInstance()
{
	if (!m_s_pUniqueFactory)
	{
		m_s_pUniqueFactory = MakeUniquePtr<HrGeometryFactory>();
	}

	return *m_s_pUniqueFactory;
}

void HrGeometryFactory::ReleaseInstance()
{
	m_s_pUniqueFactory.reset();
}

HrSceneNode* HrGeometryFactory::CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	HrGeometryBox* pBox = HR_NEW HrGeometryBox(nLength, nWidth, nHeight);
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode(pBox);

	return pSceneNode;
}

