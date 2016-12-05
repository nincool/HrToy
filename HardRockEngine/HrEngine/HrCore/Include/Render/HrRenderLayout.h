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
		virtual ~HrRenderLayout();

		void SetTopologyType(EnumTopologyType topologyType);
		EnumTopologyType GetTopologyType();
		
		void SetIndexBufferType(EnumIndexType indexType);
		 EnumIndexType GetIndexBufferType();

		uint32 GetVertexSize();
		
		void BindVertexBuffer(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, std::vector<HrVertexElement>& vecVertexElement);

		 void BindIndexBuffer(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, EnumIndexType indexType);

		bool UseIndices();

		uint32 GetIndicesNum() const;
		uint32 GetVerticesNum() const;

		void SetStartVertexLocaltion(uint32 nStartLocation);
		uint32 GetStartVertexLocaltion() const;

		void SetStartIndexLocation(uint32 nStartLocation);
		uint32 GetStartIndexLocation() const;
	protected:
		EnumTopologyType m_topologyType;
		EnumIndexType m_indexBufferType;

		HrVertex* m_pVertex;

		HrGraphicsBuffer* m_pHDVertexBuffer;
		HrGraphicsBuffer* m_pHDIndexBuffer;

		uint32 m_nVertices;
		uint32 m_nIndices;

		uint32 m_nIndexStartLocation;
		uint32 m_nVertexStartLocation;
	};
}

#endif




