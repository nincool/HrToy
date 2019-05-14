#pragma once
#include "HrEngine.h"
#include "HrConvertUtil.h"
#include "HrMeshView.h"
#include "PropertiesWnd.h"

namespace Hr
{
	class HrRenderApp;
	class HrConvertUtil;
	class HrManager
	{
	public:
		HrManager(HrMeshView* pMeshView, HrRenderApp* pRenderApp, CPropertiesWnd* pPropertiesWnd);
		~HrManager();

		void LoadOriginalMeshData(const std::string& strFileName);
		void LoadHrMeshData(const std::string& strFileName);

		HrMeshView* GetMeshView();
		HrRenderApp* GetRenderApp();
		CPropertiesWnd* GetPropertiesWnd();

		std::shared_ptr<HrConvertUtil> GetConvertUtil();

	protected:
		HrMeshView* m_pMeshClassView; //×ó±ßµÄÊôÐÔ¿ò
		HrRenderApp* m_pRenderApp;
		CPropertiesWnd* m_pPropertiesWnd;

		std::shared_ptr<HrConvertUtil> m_pConvertUtil;
	};


}
