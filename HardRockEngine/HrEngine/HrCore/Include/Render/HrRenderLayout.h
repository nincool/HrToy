#ifndef _HR_RENDERLATOUT_H_
#define _HR_RENDERLATOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrVertex.h"
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
		
		void BindVertexBuffer(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, const std::vector<HrVertexElement>& vecVertexElement);

		void BindIndexBuffer(const char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, EnumIndexType indexType);

		virtual void Active();

		size_t GetVertexStreamSize();
		uint32 GetVerticesNum();
		const std::vector<HrVertexDataPtr>& GetVertexStreams();
		
		bool UseIndices();
		uint32 GetIndicesNum();
		const HrIndexDataPtr& GetIndexStream();
		EnumIndexType GetIndexBufferType();

		size_t GetSimanticHashValue();

		uint32 GetNextVertexSemanticIndex(EnumVertexElementSemantic semantic);

		void SetInstanceNum(uint32 nInstance);
		uint32 GetInstanceNum();
	private:
		size_t CreateVertexElementHashValue();
	protected:
		EnumTopologyType m_topologyType;
		bool m_bStreamsDirty;
		size_t m_nSimanticHashValue;

		std::vector<HrVertexDataPtr> m_vecVertexStreams;
		HrIndexDataPtr m_pIndexData;

		uint32 m_nInstance;
	};
}

#endif




