#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	//kernel

	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;
	class HrWindow;
	typedef std::shared_ptr<HrWindow> HrWindowPtr;
	class HrWindowWin;
	typedef std::shared_ptr<HrWindowWin> HrWindowWinPtr;
	
	class HrModule;
	typedef class std::shared_ptr<HrModule> HrModulePtr;
	class HrWindowModule;
	typedef class std::shared_ptr<HrWindowModule> HrWindowModulePtr;;
	class HrScheduler;
	typedef std::shared_ptr<HrScheduler> HrSchedulerPtr;
	class HrSceneModule;
	typedef class std::shared_ptr<HrSceneModule> HrSceneModulePtr;
	class HrEventSystemModule;
	typedef class std::shared_ptr<HrEventSystemModule> HrEventSystemModulePtr;
	class HrResourceModule;
	typedef class std::shared_ptr<HrResourceModule> HrResourceModulePtr;
	class HrRenderModule;
	typedef class std::shared_ptr<HrRenderModule> HrRenderModulePtr;

	//Render
	class HrRenderFactory;
	typedef std::shared_ptr<HrRenderFactory> HrRenderFactoryPtr;
	class HrRenderSystem;
	typedef std::shared_ptr<HrRenderSystem> HrRenderSystemPtr;
	class HrForwardRenderSystem;
	typedef std::shared_ptr<HrForwardRenderSystem> HrForwardRenderSystemPtr;
	class HrDeferredRenderSystem;
	typedef std::shared_ptr<HrDeferredRenderSystem> HrDeferredRenderSystemPtr;
	class HrRenderProcessing;
	typedef std::shared_ptr<HrRenderProcessing> HrRenderProcessingPtr;

	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;
	class HrRenderFrame;
	typedef std::shared_ptr<HrRenderFrame> HrRenderFramePtr;
	class HrViewPort;
	typedef std::shared_ptr<HrViewPort> HrViewPortPtr;
	class HrViewPortDeferredInfo;
	typedef std::shared_ptr<HrViewPortDeferredInfo> HrViewPortDeferredInfoPtr;
	class HrRenderTarget;
	typedef std::shared_ptr<HrRenderTarget> HrRenderTargetPtr;
	class HrRenderTextureTarget;
	typedef std::shared_ptr<HrRenderTextureTarget> HrRenderTextureTargetPtr;

	class HrDepthStencil;
	typedef std::shared_ptr<HrDepthStencil> HrDepthStencilPtr;

	class HrDeferredGBufferData;
	typedef std::shared_ptr<HrDeferredGBufferData> HrDeferredGBufferDataPtr;

	//renderable
	class HrVertexElement;
	class HrVertex;
	typedef std::shared_ptr<HrVertex> HrVertexPtr;
	class HrVertexData;
	typedef std::shared_ptr<HrVertexData> HrVertexDataPtr;
	class HrIndexData;
	typedef std::shared_ptr<HrIndexData> HrIndexDataPtr;
	class HrGraphicsBuffer;
	typedef std::shared_ptr<HrGraphicsBuffer> HrGraphicsBufferPtr;
	class HrRenderLayout;
	typedef std::shared_ptr<HrRenderLayout> HrRenderLayoutPtr;
	class HrRenderable;
	typedef std::shared_ptr<HrRenderable> HrRenderablePtr;
	class HrStaticMeshRenderable;
	typedef std::shared_ptr<HrStaticMeshRenderable> HrStaticMeshRenderablePtr;
	class HrSkinnedMeshRenderable;
	typedef std::shared_ptr<HrSkinnedMeshRenderable> HrSkinnedMeshRenderablePtr;

	class HrRenderQueue;
	typedef std::shared_ptr<HrRenderQueue> HrRenderQueuePtr;
	class HrRenderQueueManager;
	typedef std::shared_ptr<HrRenderQueueManager> HrRenderQueueManagerPtr;

	//effect
	class HrRenderPass;
	typedef std::shared_ptr<HrRenderPass> HrRenderPassPtr;
	class HrRenderTechnique;
	typedef std::shared_ptr<HrRenderTechnique> HrRenderTechniquePtr;
	class HrRenderEffect;
	typedef std::shared_ptr<HrRenderEffect> HrRenderEffectPtr;
	class HrRenderParamDefine;
	class HrRenderEffectParameter;
	typedef std::shared_ptr<HrRenderEffectParameter> HrRenderEffectParameterPtr;
	class HrRenderEffectConstantBuffer;
	typedef std::shared_ptr<HrRenderEffectConstantBuffer> HrRenderEffectConstantBufferPtr;
	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;
	class HrShader;
	typedef std::shared_ptr<HrShader> HrShaderPtr;
	class HrRenderFrameParameters;
	typedef std::unique_ptr<HrRenderFrameParameters> HrRenderFrameParametersPtr;
	class HrRenderParamDefine;
	typedef std::shared_ptr<HrRenderParamDefine> HrRenderParamDefinePtr;

	//renderstate;
	class HrBlendState;
	typedef std::shared_ptr<HrBlendState> HrBlendStatePtr;
	class HrDepthStencilState;
	typedef std::shared_ptr<HrDepthStencilState> HrDepthStencilStatePtr;
	class HrSamplerState;
	typedef std::shared_ptr<HrSamplerState> HrSamplerStatePtr;
	class HrRasterizerState;
	typedef std::shared_ptr<HrRasterizerState> HrRasterizerStatePtr;

	//light
	class HrLight;
	typedef std::shared_ptr<HrLight> HrLightPtr;
	class HrDirectionalLight;
	typedef std::shared_ptr<HrLight> HrDirectionalLightPtr;

	//shadow
	class HrShadowMap;
	typedef std::shared_ptr<HrShadowMap> HrShadowMapPtr;
	class HrDeferredRender;
	typedef std::shared_ptr<HrDeferredRender> HrDeferredRenderPtr;

	//Scene
	class HrSceneLightData;
	typedef std::shared_ptr<HrSceneLightData> HrSceneLightDataPtr;
	class HrScene;
	typedef std::shared_ptr<HrScene> HrScenePtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
	class HrSceneNode;
	typedef std::shared_ptr<HrSceneNode> HrSceneNodePtr;
	class HrTransform;
	typedef std::shared_ptr<HrTransform> HrTransformPtr;
	class HrSceneObject;
	typedef std::shared_ptr<HrSceneObject> HrSceneObjectPtr;
	class HrSceneObjectComponent;
	typedef std::shared_ptr<HrSceneObjectComponent> HrSceneObjectComponentPtr;
	class HrCameraComponet;
	typedef std::shared_ptr<HrCameraComponet> HrCameraComponentPtr;
	class HrTrackBallCameraController;
	typedef std::shared_ptr<HrTrackBallCameraController> HrTrackBallCameraComponentPtr;
	class HrLightComponent;
	typedef std::shared_ptr<HrLightComponent> HrLightComponentPtr;
	class HrRenderableComponent;
	typedef std::shared_ptr<HrRenderableComponent> HrRenderableComponentPtr;
	class HrInstanceBatchComponent;
	typedef std::shared_ptr<HrInstanceBatchComponent> HrInstanceBatchComponentPtr;

	class HrOctNode;
	class HrOctree;
	class HrOctreeSceneManager;

	//Event
	class HrEvent;
	typedef std::shared_ptr<HrEvent> HrEventPtr;
	class HrEventMouse;
	typedef std::shared_ptr<HrEventMouse> HrEventMousePtr;
	class HrEventKeyboard;
	typedef std::shared_ptr<HrEventKeyboard> HrEventKeyboardPtr;
	class HrEventCustom;
	typedef std::shared_ptr<HrEventCustom> HrEventCustomPtr;
	class HrEventListenerKeyboard;
	typedef std::shared_ptr<HrEventListenerKeyboard> HrEventListenerKeyboardPtr;
	class HrEventListenerMouse;
	typedef std::shared_ptr<HrEventListenerMouse> HrEventListenerMousePtr;
	class HrEventListener;
	typedef std::shared_ptr<HrEventListener> HrEventListenerPtr;
	class HrEventDispatcher;
	typedef std::shared_ptr<HrEventDispatcher> HrEventDispatcherPtr;

	//Assets
	class HrStreamData;
	typedef std::shared_ptr<HrStreamData> HrStreamDataPtr;
	class HrResource;
	typedef std::shared_ptr<HrResource> HrResourcePtr;
	class HrMeshModel;
	typedef std::shared_ptr<HrMeshModel> HrMeshModelPtr;
	class HrMeshModelObject;
	typedef std::shared_ptr<HrMeshModelObject> HrMeshModelObjectPtr;
	class HrImage;
	class HrTexture;
	typedef std::shared_ptr<HrTexture> HrTexturePtr;
	class HrMesh;
	typedef std::shared_ptr<HrMesh> HrMeshPtr;
	class HrSubMesh;
	typedef std::shared_ptr<HrSubMesh> HrSubMeshPtr;
	class HrModelLoader;
	typedef std::shared_ptr<HrModelLoader> HrModelLoaderPtr;
	class HrMaterial;
	typedef std::shared_ptr<HrMaterial> HrMaterialPtr;
	class HrPrefabData;
	typedef std::shared_ptr<HrPrefabData> HrPrefabDataPtr;
	class HrShaderCompiler;
	typedef std::shared_ptr<HrShaderCompiler> HrShaderCompilerPtr;

	class HrResourceManager;
	typedef std::shared_ptr<HrResourceManager> HrResourceManagerPtr;

	//InstanceBatch
	class HrInstanceBatch;
	typedef std::shared_ptr<HrInstanceBatch> HrInstanceBatchPtr;
	class HrInstanceBatchHW;
	typedef std::shared_ptr<HrInstanceBatchHW> HrInstanceBatchHWPtr;
	class HrInstanceBatchObject;
	typedef std::shared_ptr<HrInstanceBatchObject> HrInstanceBatchObjectPtr;
}


#endif



