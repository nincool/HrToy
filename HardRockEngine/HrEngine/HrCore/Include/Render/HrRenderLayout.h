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
		virtual uint32 GetVertextSize() override;
		virtual void BindVertextBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrVertextElement* pVertexElementArr
			, uint32 nVertexElementLength) override;

	protected:
		EnumTopologyType m_topologyType;

		HrVertext* m_pVertext;

		IGraphicsBuffer* m_pHardwareBuffer;
	};
}

#endif




