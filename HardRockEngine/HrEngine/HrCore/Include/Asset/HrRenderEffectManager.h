#ifndef _HR_RENDEREFFECTMANAGER_H_
#define _HR_RENDEREFFECTMANAGER_H_

#include "HrCore/Include/Asset/HrResourceManager.h"

namespace Hr
{
	class HrRenderEffectManager : public HrResourceManager
	{
	public:
		HrRenderEffectManager();
		~HrRenderEffectManager();

		virtual void InitResourceManager() override;
		virtual IResource* LoadResource(std::string strName, std::string strFilePath) override;
		virtual IResource* GetResource(std::string strName) override;

		HrRenderEffect* GetRenderEffect(std::string strName);
	private:
		HrRenderEffect* CreateEffect(std::string strName, std::string strFilePath);
	};
}


#endif

