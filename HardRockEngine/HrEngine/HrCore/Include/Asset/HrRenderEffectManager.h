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

	
	private:
		HrRenderEffect* CreateEffect(std::string strName, std::string strFilePath);


	private:
		IShaderCompilerPtr m_pShareShaderCompiler;
	};
}


#endif

