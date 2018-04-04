#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	//kernel
	class HrCoreComponentRender;
	typedef class std::shared_ptr<HrCoreComponentRender> HrCoreComponentRenderPtr;
	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;
	class HrWindow;
	typedef std::shared_ptr<HrWindow> HrWindowPtr;
	class HrWindowWin;
	typedef std::shared_ptr<HrWindowWin> HrWindowWinPtr;
	class HrCoreComponentWin;
	typedef class std::shared_ptr<HrCoreComponentWin> HrCoreComponentWinPtr;
	class HrScheduler;
	typedef std::shared_ptr<HrScheduler> HrSchedulerPtr;
	class HrCoreComponentScene;
	typedef class std::shared_ptr<HrCoreComponentScene> HrCoreComponentScenePtr;
	class HrCoreComponentEvent;
	typedef class std::shared_ptr<HrCoreComponentEvent> HrCoreComponentEventPtr;
	class HrCoreComponentResource;
	typedef class std::shared_ptr<HrCoreComponentResource> HrCoreComponentResourcePtr;

	//Render
	class HrRenderFactory;
	typedef std::shared_ptr<HrRenderFactory> HrRenderFactoryPtr;
	class HrRenderSystem;
	typedef std::shared_ptr<HrRenderSystem> HrRenderSystemPtr;
	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;
	class HrRenderFrame;
	typedef std::shared_ptr<HrRenderFrame> HrRenderFramePtr;
	class HrViewPort;
	typedef std::shared_ptr<HrViewPort> HrViewPortPtr;
	class HrRenderTarget;
	typedef std::shared_ptr<HrRenderTarget> HrRenderTargetPtr;
	class HrDepthStencil;
	typedef std::shared_ptr<HrDepthStencil> HrDepthStencilPtr;
	
	class HrVertexElement;
	class HrVertex;
	typedef std::shared_ptr<HrVertex> HrVertexPtr;
	class HrVertexData;
	typedef std::shared_ptr<HrVertexData> HrVertexDataPtr;
	class HrGraphicsBuffer;
	typedef std::shared_ptr<HrGraphicsBuffer> HrGraphicsBufferPtr;
	class HrRenderQueue;
	typedef std::shared_ptr<HrRenderQueue> HrRenderQueuePtr;
	class HrRenderLayout;
	typedef std::shared_ptr<HrRenderLayout> HrRenderLayoutPtr;
	class HrRenderable;
	typedef std::shared_ptr<HrRenderable> HrRenderablePtr;
	class HrStaticMeshRenderable;
	typedef std::shared_ptr<HrStaticMeshRenderable> HrStaticMeshRenderablePtr;
	class HrSkinnedMeshRenderable;
	typedef std::shared_ptr<HrSkinnedMeshRenderable> HrSkinnedMeshRenderablePtr;

	//InstanceBatch
	class HrInstanceBatch;
	typedef std::shared_ptr<HrInstanceBatch> HrInstanceBatchPtr;
	class HrInstanceBatchHW;
	typedef std::shared_ptr<HrInstanceBatchHW> HrInstanceBatchHWPtr;
	class HrInstanceBatchObject;
	typedef std::shared_ptr<HrInstanceBatchObject> HrInstanceBatchObjectPtr;

	class HrRenderPass;
	typedef std::shared_ptr<HrRenderPass> HrRenderPassPtr;
	class HrRenderTechnique;
	typedef std::shared_ptr<HrRenderTechnique> HrRenderTechniquePtr;
	class HrRenderEffect;
	typedef std::shared_ptr<HrRenderEffect> HrRenderEffectPtr;
	class HrRenderParamDefine;
	class HrRenderEffectParameter;
	typedef std::shared_ptr<HrRenderEffectParameter> HrRenderEffectParameterPtr;
	class HrRenderEffectStructParameter;
	typedef std::shared_ptr<HrRenderEffectStructParameter> HrRenderEffectStructParameterPtr;
	class HrRenderEffectConstantBuffer;
	typedef std::shared_ptr<HrRenderEffectConstantBuffer> HrRenderEffectConstantBufferPtr;
	
	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;
	
	class HrSamplerState;
	typedef std::shared_ptr<HrSamplerState> HrSamplerStatePtr;

	class HrDepthStencilState;
	class HrBlendState;
	class HrRasterizerState;
	class HrLight;
	typedef std::shared_ptr<HrLight> HrLightPtr;
	class HrDirectionalLight;
	typedef std::shared_ptr<HrLight> HrDirectionalLightPtr;
	class HrShader;
	typedef std::shared_ptr<HrShader> HrShaderPtr;
	class HrRenderFrameParameters;
	typedef std::unique_ptr<HrRenderFrameParameters> HrRenderFrameParametersPtr;
	class HrRenderParamDefine;
	typedef std::shared_ptr<HrRenderParamDefine> HrRenderParamDefinePtr;



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
	class HrLightComponent;
	typedef std::shared_ptr<HrLightComponent> HrLightComponentPtr;
	class HrRenderableComponent;
	typedef std::shared_ptr<HrRenderableComponent> HrRenderableComponentPtr;
	class HrInstanceBatchComponent;
	typedef std::shared_ptr<HrInstanceBatchComponent> HrInstanceBatchComponentPtr;

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
	class HrModel;
	typedef std::shared_ptr<HrModel> HrModelPtr;
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
	class HrShaderCompiler;
	typedef std::shared_ptr<HrShaderCompiler> HrShaderCompilerPtr;

	class HrResourceManager;
	typedef std::shared_ptr<HrResourceManager> HrResourceManagerPtr;

	//Asset


	class HrComponentFactory;
	typedef std::shared_ptr<HrComponentFactory> HrComponentFactoryPtr;
	class HrGeometryFactory;
	typedef std::shared_ptr<HrGeometryFactory> HrGeometryFactoryPtr;
	class HrGeometryBox;
}


#endif



