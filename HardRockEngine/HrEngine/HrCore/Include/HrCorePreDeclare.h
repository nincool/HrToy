#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	//kernel
	class HrRenderCoreComponent;
	typedef class std::shared_ptr<HrRenderCoreComponent> HrRenderCoreComponentPtr;
	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;
	class HrWindow;
	typedef std::shared_ptr<HrWindow> HrWindowPtr;
	class HrWindowWin;
	typedef std::shared_ptr<HrWindowWin> HrWindowWinPtr;
	class HrWinCoreComponent;
	typedef class std::shared_ptr<HrWinCoreComponent> HrWinCoreComponentPtr;
	class HrScheduler;
	typedef std::shared_ptr<HrScheduler> HrSchedulerPtr;
	typedef std::weak_ptr<HrScheduler> HrWeakSchedulerPtr;
	class HrSceneCoreComponent;
	typedef class std::shared_ptr<HrSceneCoreComponent> HrSceneCoreComponentPtr;

	//Render
	class HrRenderFactory;
	typedef std::shared_ptr<HrRenderFactory> HrRenderFactoryPtr;
	class HrRenderSystem;
	typedef std::shared_ptr<HrRenderSystem> HrRenderSystemPtr;
	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;
	class HrRenderFrame;
	typedef std::shared_ptr<HrRenderFrame> HrRenderFramePtr;

	class HrVertexElement;
	class HrVertex;
	class HrGraphicsBuffer;
	class HrRenderQueue;
	typedef std::shared_ptr<HrRenderQueue> HrRenderQueuePtr;
	class HrRenderable;
	class HrRenderPass;
	class HrRenderLayout;
	class HrRenderTechnique;
	class HrRenderEffect;
	class HrRenderParamDefine;
	class HrRenderEffectParameter;
	class HrRenderEffectStructParameter;
	class HrRenderEffectConstantBuffer;
	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;
	class HrSamplerState;
	class HrDepthStencilState;
	class HrBlendState;
	class HrRasterizerState;
	class HrLight;
	typedef std::shared_ptr<HrLight> HrLightPtr;
	class HrDirectionalLight;
	typedef std::shared_ptr<HrLight> HrDirectionalLightPtr;
	class HrShader;
	class HrRenderFrameParameters;
	typedef std::unique_ptr<HrRenderFrameParameters> HrRenderFrameParametersPtr;
	class HrViewPort;
	typedef std::shared_ptr<HrViewPort> HrViewPortPtr;
	class HrRenderTarget;
	typedef std::shared_ptr<HrRenderTarget> HrRenderTargetPtr;

	//Asset
	class HrTexture;
	class HrStreamData;
	typedef std::shared_ptr<HrStreamData> HrStreamDataPtr;
	class HrResource;
	class HrResourceManager;
	class HrModelLoader;
	typedef std::shared_ptr<HrModelLoader> HrModelLoaderPtr;
	class HrMesh;
	class HrSubMesh;
	class HrPrefabModel;
	class HrMaterial;
	class HrShaderCompiler;
	typedef std::shared_ptr<HrShaderCompiler> HrShaderCompilerPtr;
	class HrComponentFactory;
	typedef std::shared_ptr<HrComponentFactory> HrComponentFactoryPtr;
	class HrGeometryFactory;
	typedef std::shared_ptr<HrGeometryFactory> HrGeometryFactoryPtr;
	class HrGeometryBox;

	//Scene
	class HrScene;
	typedef std::shared_ptr<HrScene> HrScenePtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
	class HrSceneNode;
	typedef std::shared_ptr<HrSceneNode> HrSceneNodePtr;
	class HrCameraNode;
	class HrLightNode;
	class HrTransform;
	typedef std::shared_ptr<HrTransform> HrTransformPtr;

	//Event
	class HrEvent;
	class HrEventListenerKeyboard;
	typedef std::shared_ptr<HrEventListenerKeyboard> HrEventListenerKeyboardPtr;
	class HrEventListenerMouse;
	typedef std::shared_ptr<HrEventListenerMouse> HrEventListenerMousePtr;
	class HrEventListener;
	typedef std::shared_ptr<HrEventListener> HrEventListenerPtr;
	class HrEventDispatcher;
	typedef std::shared_ptr<HrEventDispatcher> HrEventDispatcherPtr;
}


#endif



