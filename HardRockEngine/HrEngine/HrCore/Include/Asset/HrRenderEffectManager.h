/************************************************************************ 
* 
*   DocName£∫HrRenderEffectManager
* 
*   Brief£∫ Shaderπ‹¿Ì∆˜
* 
*   Author: Hr  
* 
*   Comment: 
* 
*   Date: [5/19/2016 By Hr]
*
************************************************************************/ 
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
		virtual HrResource* LoadResource(std::string strName, std::string strFilePath) override;
		virtual HrResource* GetResource(std::string strName) override;

		HrRenderEffect* GetRenderEffect(std::string strName);
	private:
		HrRenderEffect* CreateEffect(std::string strName, std::string strFilePath);
	};
}


#endif

