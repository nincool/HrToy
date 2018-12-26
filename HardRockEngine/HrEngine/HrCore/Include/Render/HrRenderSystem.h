#ifndef _HR_RENDERSYSTEM_H_
#define _HR_RENDERSYSTEM_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HR_CORE_API HrRenderSystem
	{
	public:
		HrRenderSystem();
		virtual ~HrRenderSystem();

		virtual void StartRenderProcess();
		const HrSceneNodePtr& GetScreenQuadRenderable();
		const HrRenderFramePtr& GetScreenFrameBuffer();
	protected:
		EnumRenderingPath m_renderPath;
		std::list< HrRenderProcessingPtr > m_lisRenderProcessing;
		HrSceneNodePtr m_pScreenQuad;
		HrRenderFramePtr m_pScreenFrameBuffer;
	};

	///////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////
	class HrForwardRenderSystem : public HrRenderSystem
	{
	public:
		HrForwardRenderSystem();
		~HrForwardRenderSystem();
		
		virtual void StartRenderProcess() override;
	protected:
		void BuildRenderProcesses();


	};


	///////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////

	class HrDeferredRenderSystem : public HrRenderSystem
	{
	public:
		HrDeferredRenderSystem();
		~HrDeferredRenderSystem();

		virtual void StartRenderProcess() override;

		const HrRenderFramePtr& GetDeferredRenderFrame();
	protected:
		void BuildRenderProcesses();
	protected:
		HrRenderFramePtr m_pDeferredFrameBuffer;
	};

	//class HrDeferredGBufferData
	//{
	//public:
	//	HrTexturePtr m_pGBufferPosition;
	//	HrTexturePtr m_pGBufferNormal;
	//	HrTexturePtr m_pGBufferAlbedo;
	//};

	//class HrDeferredRender
	//{
	//public:
	//	HrDeferredRender();
	//	~HrDeferredRender();

	//	const HrRenderFramePtr& GetDeferredFrameBuffer();
	//	const HrRenderablePtr& GetScreenQuadRenderable();
	//	const HrSceneNodePtr& GetSceneQuadNode();
	//protected:
	//	void CreateScreenQuad();
	//	HrSceneNodePtr CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight);
	//	HrSceneNodePtr CreateSceneNode(const std::string& strName);

	//protected:
	//	HrRenderFramePtr m_pDeferredFrameBuffer;
	//	HrSceneNodePtr m_pSceneQuadNode;
	//	HrRenderablePtr m_pScreenQuad;

	//	std::shared_ptr<HrDeferredGBufferData> m_pDeferredGBufferData;

	//};

	//class HrScreenQuadRenderable : public HrStaticMeshRenderable
	//{
	//public:
	//	HrScreenQuadRenderable(const HrSubMeshPtr& pSubMesh, const HrDeferredGBufferDataPtr& pDeferredGBufferData) : HrStaticMeshRenderable(pSubMesh)
	//	{
	//		m_pDeferredGBufferData = pDeferredGBufferData;
	//	};

	//	virtual void OnRenderBegin() override;
	//	//virtual void Render(const HrRenderTechniquePtr& pRenderTech = nullptr);
	//	virtual void OnRenderEnd() override;

	//protected:
	//	virtual void UpdateRenderEffectParam() override;

	//private:
	//	HrDeferredGBufferDataPtr m_pDeferredGBufferData;
	//};
}


#endif

