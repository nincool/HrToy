#ifndef _HR_RENDEREFFECTCONSTANTBUFFER_H_
#define _HR_RENDEREFFECTCONSTANTBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderEffectParameter : public boost::noncopyable
	{
	public:
		HrRenderEffectParameter();
		~HrRenderEffectParameter();

	private:

	};

	class HrRenderEffectConstantBuffer : public boost::noncopyable
	{
	public:
		HrRenderEffectConstantBuffer();
		~HrRenderEffectConstantBuffer();

		
	private:
		HrGraphicsBuffer* m_pConstantBuffer;
	};
}

#endif



