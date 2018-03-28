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
		
		void BindVertexBuffer(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, const std::vector<HrVertexElement>& vecVertexElement);

		void BindIndexBuffer(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, EnumIndexType indexType);

		virtual void Active();

		bool UseIndices();

		size_t GetVertexStreamSize();

		uint32 GetVerticesNum();

		const std::vector<HrVertexDataPtr>& GetVertexStreams();
	protected:
		EnumTopologyType m_topologyType;
		EnumIndexType m_indexBufferType;

		bool m_bStreamsDirty;
		std::vector<HrVertexDataPtr> m_vecVertexStreams;
	};
}

#endif




