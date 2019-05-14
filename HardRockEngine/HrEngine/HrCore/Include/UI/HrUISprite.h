#ifndef _HR_UISPRITE_H_
#define _HR_UISPRITE_H_

#include "HrCore/Include/UI/HrUIWidget.h"

namespace Hr
{
	class HR_CORE_API HrUISprite : public HrUIWidget
	{
	public:
		HrUISprite(const std::string& strFileName);
		virtual ~HrUISprite();

		virtual void Render();

	private:
		bool InitWidthTexture(const HrTexturePtr& pTexture);
		void RebuildQuad();
	private:
	
		HrTexturePtr m_pTexture;


		float m_fWidth;
		float m_fHeight;
	};
}

#endif
