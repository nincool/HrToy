#ifndef _HR_UIWIDGET_H_
#define _HR_UIWIDGET_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrMeshModel.h"
#include "HrCore/Include/Event/HrEvent.h"

namespace Hr
{
	class HR_CORE_API HrUIWidget
	{
	public:
		HrUIWidget();
		virtual ~HrUIWidget();

		const HrRenderablePtr& GetRenderable();

		virtual float2& GetContentSize();

		virtual void OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		virtual void OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		virtual void OnMouseMove(const HrEventPtr& pEvent);

	protected:
		bool IsScreenPointInRect();
	protected:
		HrQuad_P_UV m_quad;
		HrRenderablePtr m_pRenderable;
		HrMeshPtr m_pMesh;

		float2 m_contentSize;
	};
}


#endif
