#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;
	class HrWindow;
	typedef std::shared_ptr<HrWindow> HrWindowPtr;
	class HrWindowWin;
	typedef std::shared_ptr<HrWindowWin> HrWindowWinPtr;

	class HrRenderFactory;
	typedef std::shared_ptr<HrRenderFactory> HrRenderFactoryPtr;
	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;

	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;


	class HrScene;
	typedef std::shared_ptr<HrScene> HrScenePtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
	class HrSceneNode;
	typedef std::shared_ptr<HrSceneNode> HrSceneNodePtr;
	class HrCameraNode;

	class HrVertexElement;
	class HrVertex;
	class HrGraphicsBuffer;
	class HrHardwareBuffer;
	class HrRenderQueue;
	typedef std::shared_ptr<HrRenderQueue> HrRenderQueuePtr;
	class HrRenderable;
	class HrRenderPass;
	class HrRenderLayout;
	class HrRenderTechnique;
	class HrRenderEffect;
	class HrShader;
	class HrShaderParams;
	class HrRenderConstantBuffer;
	class HrRenderParameter;
	class HrRenderFrameParameters;
	typedef std::unique_ptr<HrRenderFrameParameters> HrRenderFrameParametersPtr;
	class HrViewPort;
	class HrRenderTarget;
	typedef std::shared_ptr<HrRenderTarget> HrRenderTargetPtr;

	class HrStreamData;
	class HrResourceManagerFactory;
	typedef std::shared_ptr<HrResourceManagerFactory> HrResourceManagerFactoryPtr;
	class HrResource;
	class HrResourceManager;
	class HrRenderEffectManager;
	typedef std::shared_ptr<HrRenderEffectManager> HrRenderEffectManagerPtr;
	class HrRenderEffect;
	class HrComponentFactory;
	typedef std::shared_ptr<HrComponentFactory> HrComponentFactoryPtr;
	class HrAssetSystemFactory;
	typedef std::shared_ptr<HrAssetSystemFactory> HrAssetSystemFactoryPtr;
	class HrGeometryFactory;
	typedef std::shared_ptr<HrGeometryFactory> HrGeometryFactoryPtr;
	
	class HrGeometryBox;

	class HrEvent;
	class HrEventListenerKeyboard;
	typedef std::shared_ptr<HrEventListenerKeyboard> HrEventListenerKeyboardPtr;
	class HrEventListener;
	typedef std::shared_ptr<HrEventListener> HrEventListenerPtr;
	class HrEventDispatcher;
	typedef std::shared_ptr<HrEventDispatcher> HrEventDispatcherPtr;
	
}


#endif



