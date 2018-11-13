#ifndef _HR_DEPTHSTENCIL_H_
#define _HR_DEPTHSTENCIL_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HR_CORE_API HrDepthStencil
	{
	public:
		HrDepthStencil(uint32 nWidth, uint32 nHeight, EnumPixelFormat format);
		virtual ~HrDepthStencil();

		uint32 GetWidth() const;
		uint32 GetHeight() const;

		virtual HrTexturePtr GetDepthStencilSRV();
	protected:
		uint32 m_nWidth;
		uint32 m_nHeight;
		EnumPixelFormat m_format;
	};
}

#endif
