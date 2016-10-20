#ifndef _HR_RENDEREFFECT_H_
#define _HR_RENDEREFFECT_H_

#include "HrResource.h"

namespace Hr
{
	class HrRenderEffect : public HrResource
	{
	public:
		HrRenderEffect(std::string strEffectName, std::string strFilePath);
		virtual ~HrRenderEffect();

		virtual size_t HashName() override;
		virtual void Load() override;
		virtual void Unload() override;

		HrRenderTechnique* GetTechnique(std::string strTechniqueName);

	private:
		size_t m_nHashName;

		std::string m_strEffectName;
		std::string m_strFilePath;
		std::string m_strEffectFile;
		
		std::vector<HrRenderTechnique*> m_vecRenderTechnique;
		
	};
}

#endif

