#ifndef _HR_RENDEREFFECT_H_
#define _HR_RENDEREFFECT_H_

#include "HrCore/Include/Asset/IResource.h"

namespace Hr
{
	class HrRenderEffect : public IResource
	{
	public:
		HrRenderEffect(std::string strEffectName, std::string strFilePath);
		virtual ~HrRenderEffect();

		virtual void Load() override;
		virtual void Unload() override;
	private:
		std::string m_strEffectName;
		std::string m_strFilePath;

		std::string m_strEffectFile;
		
		std::vector<HrRenderTechnique*> m_vecRenderTechnique;

	};
}

#endif



