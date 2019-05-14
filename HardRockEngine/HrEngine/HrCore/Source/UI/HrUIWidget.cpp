#include "UI/HrUIWidget.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrUIWidget::HrUIWidget()
{

}

HrUIWidget::~HrUIWidget()
{

}


const HrRenderablePtr& HrUIWidget::GetRenderable()
{
	return m_pRenderable;
}

void HrUIWidget::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		break;
	case HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		break;
	case HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrUIWidget::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		break;
	case HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		break;
	case HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrUIWidget::OnMouseMove(const HrEventPtr& pEvent)
{

}

float2& HrUIWidget::GetContentSize()
{
	return m_contentSize;
}

bool HrUIWidget::IsScreenPointInRect()
{
	//todo 当前活动的摄像机
	return false;
}
