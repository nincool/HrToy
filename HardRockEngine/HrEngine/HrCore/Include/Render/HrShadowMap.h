#ifndef _HR_SHADOWMAP_H_
#define _HR_SHADOWMAP_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrMeshRenderable.h"

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

	/////////////////////////////////////////////////////////////////////////////////
	//≤‚ ‘≤‚ ‘≤‚ ‘
	/////////////////////////////////////////////////////////////////////////////////
	class HrScreenQuadRenderable : public HrStaticMeshRenderable
	{
	public:
		HrScreenQuadRenderable(const HrSubMeshPtr& pSubMesh, const HrDeferredGBufferDataPtr& pDeferredGBufferData) : HrStaticMeshRenderable(pSubMesh) 
		{
			m_pDeferredGBufferData = pDeferredGBufferData;
		};

		virtual void OnRenderBegin() override;
		//virtual void Render(const HrRenderTechniquePtr& pRenderTech = nullptr);
		virtual void OnRenderEnd() override;

	protected:
		virtual void UpdateRenderEffectParam() override;

	private:
		HrDeferredGBufferDataPtr m_pDeferredGBufferData;
	};

	class HrDeferredGBufferData
	{
	public:
		HrTexturePtr m_pGBufferPosition;
		HrTexturePtr m_pGBufferNormal;
		HrTexturePtr m_pGBufferAlbedo;
	};

	class HrDeferredRender
	{
	public:
		HrDeferredRender();
		~HrDeferredRender();

		const HrRenderFramePtr& GetDeferredFrameBuffer();
		const HrRenderablePtr& GetScreenQuadRenderable();
		const HrSceneNodePtr& GetSceneQuadNode();
	protected:
		void CreateScreenQuad();
		HrSceneNodePtr CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight);
		HrSceneNodePtr CreateSceneNode(const std::string& strName);

	protected:
		HrRenderFramePtr m_pDeferredFrameBuffer;
		HrSceneNodePtr m_pSceneQuadNode;
		HrRenderablePtr m_pScreenQuad;

		std::shared_ptr<HrDeferredGBufferData> m_pDeferredGBufferData;

	};
}

#endif





