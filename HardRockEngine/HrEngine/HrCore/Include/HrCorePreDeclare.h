#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	class IApplication;
	typedef std::unique_ptr<IApplication> IApplicationPtr;
	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;

	class HrDirector;
	typedef std::unique_ptr<HrDirector> HrDirectorPtr;

	class HrLog;
	typedef std::unique_ptr<HrLog> HrLogPtr;

	class HrRenderFactory;
	typedef std::shared_ptr<HrRenderFactory> HrRenderFactoryPtr;
	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;

	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;

	class HrGeometryFactory;
	typedef std::unique_ptr<HrGeometryFactory> HrGeometryFactoryPtr;

	class HrScene;
	typedef std::shared_ptr<HrScene> HrScenePtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
	class HrSceneNode;
	typedef std::shared_ptr<HrSceneNode> HrSceneNodePtr;
	class HrCameraNode;

	class HrVertexElement;
	class HrVertex;
	class IGraphicsBuffer;
	class HrHardwareBuffer;
	class IRenderable;
	class HrRenderQueue;
	typedef std::shared_ptr<HrRenderQueue> HrRenderQueuePtr;
	class HrRenderPass;
	class IRenderLayout;
	class HrRenderLayout;
	class IRenderTechnique;
	class HrRenderTechnique;
	class HrRenderEffect;
	class IShader;
	class HrShaderParams;
	class HrRenderConstantBuffer;
	class HrRenderParameter;
	class HrRenderFrameParameters;
	typedef std::unique_ptr<HrRenderFrameParameters> HrRenderFrameParametersPtr;
	class HrViewPort;
	class IRenderTarget;
	typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;
	class HrRenderTarget;
	typedef std::shared_ptr<HrRenderTarget> HrRenderTargetPtr;
	class HrComponentFactory;
	typedef std::unique_ptr<HrComponentFactory> HrComponentFactoryPtr;


	class HrResourceManagerFactory;
	typedef std::unique_ptr<HrResourceManagerFactory> HrResourceManagerFactoryPtr;
	class IResource;
	class IResourceManager;
	typedef std::shared_ptr<IResourceManager> IResourceManagerPtr;
	class HrRenderEffectManager;
	class HrStreamData;
	class HrResourceLoader;
	//class IShaderCompiler;
	//typedef std::shared_ptr<IShaderCompiler> IShaderCompilerPtr;

	
	class HrGeometryBox;

}


#endif



