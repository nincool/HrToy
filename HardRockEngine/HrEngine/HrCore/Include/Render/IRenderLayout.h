#ifndef _I_RENDERLAYOUT_H_
#define _I_RENDERLAYOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/IGraphicsBuffer.h"

namespace Hr
{
	class IRenderLayout
	{
	public:


	public:

		virtual ~IRenderLayout(){}

		virtual void SetTopologyType(EnumTopologyType topologyType) = 0;
		virtual EnumTopologyType GetTopologyType() = 0;
		virtual void SetIndexBufferType(EnumIndexType indexType) = 0;
		virtual EnumIndexType GetIndexBufferType() = 0;

		virtual uint32 GetVertexSize() = 0;

		virtual void BindVertexBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrVertexElement* pVertexElementArr
			, uint32 nVertexElementLength) = 0;
		virtual void BindIndexBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, EnumIndexType indexType) = 0;

		//是否使用索引缓存
		virtual bool UseIndices() = 0;

		virtual void SetIndicesNum(uint32 nIndicesNum) = 0;
		virtual uint32 GetIndicesNum() = 0;
	};
}

#endif