#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Asset/HrGeometryTriangle.h"
#include "HrCore/Include/Scene/HrSceneNode.h"

using namespace Hr;


HrGeometryFactory::HrGeometryFactory()
{

}

HrGeometryFactory::~HrGeometryFactory()
{
}

HrSceneNode* HrGeometryFactory::Create2DTriangle()
{
	HrGeometryTriangle* pTriangle = HR_NEW HrGeometryTriangle();
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode(pTriangle);

	return pSceneNode;
}

HrSceneNode* HrGeometryFactory::CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	HrGeometryBox* pBox = HR_NEW HrGeometryBox(nLength, nWidth, nHeight);
	HrSceneNode* pSceneNode = HR_NEW HrSceneNode(pBox);

	return pSceneNode;
}

