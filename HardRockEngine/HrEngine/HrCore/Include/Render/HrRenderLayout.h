#ifndef _HR_RENDERLATOUT_H_
#define _HR_RENDERLATOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrRenderLayout 
	{
	public:
		HrRenderLayout();
		~HrRenderLayout();

		virtual void SetTopologyType(EnumTopologyType topologyType);
		virtual EnumTopologyType GetTopologyType();
		
		virtual void SetIndexBufferType(EnumIndexType indexType);
		virtual EnumIndexType GetIndexBufferType();

		virtual uint32 GetVertexSize();
		
		virtual void BindVertexBuffer(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, HrVertexElement* pVertexElementArr
			, uint32 nVertexElementLength);

		virtual void BindIndexBuffer(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, EnumIndexType indexType);

		virtual bool UseIndices();

		virtual void SetIndicesNum(uint32 nIndicesNum);
		virtual uint32 GetIndicesNum();

	protected:
		EnumTopologyType m_topologyType;
		EnumIndexType m_indexBufferType;

		HrVertex* m_pVertex;

		HrGraphicsBuffer* m_pHDVertexBuffer;
		HrGraphicsBuffer* m_pHDIndexBuffer;

		uint32 m_nVertices;
		uint32 m_nIndices;
	};
}

#endif




