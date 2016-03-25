#ifndef _HR_RENDERLATOUT_H_
#define _HR_RENDERLATOUT_H_

#include "HrCore/Include/Render/IRenderLayout.h"

namespace Hr
{
	class HR_CORE_API HrRenderLayout : public IRenderLayout
	{
	public:
		HrRenderLayout();
		~HrRenderLayout();

		virtual void SetTopologyType(EnumTopologyType topologyType) override;
		virtual EnumTopologyType GetTopologyType() override;
		virtual void SetIndexBufferType(EnumIndexType indexType) override;
		virtual EnumIndexType GetIndexBufferType() override;

		virtual uint32 GetVertexSize() override;
		virtual void BindVertexBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrVertexElement* pVertexElementArr
			, uint32 nVertexElementLength) override;

		virtual void BindIndexBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, EnumIndexType indexType) override;

		virtual bool UseIndices() override;

		virtual void SetIndicesNum(uint32 nIndicesNum) override;
		virtual uint32 GetIndicesNum() override;
	protected:
		EnumTopologyType m_topologyType;
		EnumIndexType m_indexBufferType;

		HrVertex* m_pVertex;

		IGraphicsBuffer* m_pHDVertexBuffer;
		IGraphicsBuffer* m_pHDIndexBuffer;

		uint32 m_nVertices;
		uint32 m_nIndices;
	};
}

#endif




