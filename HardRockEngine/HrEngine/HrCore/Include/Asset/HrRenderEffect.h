#ifndef _HR_RENDEREFFECT_H_
#define _HR_RENDEREFFECT_H_

#include "HrResource.h"

namespace Hr
{
	class HrRenderEffect : public HrResource
	{
	public:
		HrRenderEffect();
		virtual ~HrRenderEffect();

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		HrRenderTechnique* GetTechnique(std::string strTechniqueName);

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	private:
		size_t m_nHashName;

		std::string m_strEffectName;
		std::string m_strFilePath;
		std::string m_strEffectFile;
		
		std::vector<HrRenderTechnique*> m_vecRenderTechnique;
		
	};
}

#endif

