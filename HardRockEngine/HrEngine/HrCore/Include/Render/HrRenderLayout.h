#ifndef _HR_RENDERLATOUT_H_
#define _HR_RENDERLATOUT_H_

#include "HrCore/Include/Render/IRenderLayout.h"

namespace Hr
{
	class HR_CORE_API HrRenderLayout : public IRenderLayout
	{
	public:
		enum EnumTopologyType
		{
			TT_POINTLIST,
			TT_LINELIST,
			TT_LINETRIP,
			TT_TRIANGLELIST,
			TT_TRIANGLETRIP,
		};
	public:
		HrRenderLayout();
		~HrRenderLayout();

		virtual uint32 GetVertextSize() override;
		virtual void BindVertextBuffer(IGraphicsBuffer * pGraphicsBuffer, HrVertext* pVertext) override;

		HR_SYNTHESIZE(EnumTopologyType, m_topologyType, TopologyType);
	protected:
		HrVertext* m_pVertextStruct;

		IGraphicsBuffer* m_pHardwareBuffer;
	};
}

#endif




