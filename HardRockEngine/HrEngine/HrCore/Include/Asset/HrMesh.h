#ifndef _HR_MESH_H_
#define _HR_MESH_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"

namespace Hr
{
	class HrSubMesh
	{
		HrRenderLayout* m_pRenderLayout;
	};

	class HrMesh : public HrResource
	{
	public:
		HrMesh();
		virtual ~HrMesh();

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		HrRenderLayout* GetRenderLayout();

		void AddVertexStream(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, HrVertexElement* pVertexElementArr
			, uint32 nVertexElementLength);
		void AddIndexStream(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, EnumIndexType indexType);

		void FinishedBuildMesh();
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		HrRenderLayout* m_pRenderLayout;


	};
}


#endif



