#ifndef _HR_SHADOWMAP_H_
#define _HR_SHADOWMAP_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrShadowMap
	{
	public:
		virtual ~HrShadowMap();

		void CreateShadowTexture(uint32 nWidth, uint32 nHeight);

		void OnStartRenderFrame();
		void OnEndRenderFrame();

		const HrRenderFramePtr& GetDepthStencilFrame();
		const HrCameraPtr& GetShadowMapCamera();

		
	protected:
		HrRenderFramePtr m_pDepthStencilFrameBuffer;
		HrCameraPtr m_pShadowMapCamera;


	};
}

#endif



