#include "Asset/HrMesh.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrMesh::HrMesh()
{
	//for test
	m_pRenderLayout = HrDirector::Instance()->GetRenderFactory()->CreateRenderLayout();
}

HrMesh::~HrMesh()
{
	SAFE_DELETE(m_pRenderLayout);
}

void HrMesh::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MESH;

	m_nHashID = HrHashValue(m_strFilePath + strFileName + ".Hr_Mesh");
}

HrRenderLayout* HrMesh::GetRenderLayout()
{
	return m_pRenderLayout;
}

//void HrMesh::AddVertexStream(const char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, HrVertexElement* pVertexElementArr, uint32 nVertexElementLength)
//{
//	m_pRenderLayout->BindVertexBuffer(pBuffer, nBufferSize, usage, pVertexElementArr, nVertexElementLength);
//}
//
//void HrMesh::AddIndexStream(const char* pBuffer, uint32 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, EnumIndexType indexType)
//{
//	m_pRenderLayout->BindIndexBuffer(pBuffer, nBufferSize, usage, indexType);
//}

bool HrMesh::LoadImpl()
{
	return true;
}

bool HrMesh::UnloadImpl()
{
	return true;
}

void HrMesh::FinishedBuildMesh()
{
	m_bLoaded = true;
}

