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

	class ILog;
	class HrLog;
	typedef std::unique_ptr<HrLog> HrLogPtr;

	class IRenderFactory;
	typedef std::shared_ptr<IRenderFactory> IRenderFactoryPtr;
	class IRender;
	typedef std::shared_ptr<IRender> IRenderPtr;

	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;

	class HrGeometryFactory;
	typedef std::unique_ptr<HrGeometryFactory> HrGeometryFactoryPtr;

	class IScene;
	typedef std::shared_ptr<IScene> IScenePtr;
	class HrScene;
	typedef std::shared_ptr<HrScene> HrScenePtr;
	class ISceneManager;
	typedef std::shared_ptr<ISceneManager> ISceneManagerPtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
	class ISceneNode;
	typedef std::shared_ptr<ISceneNode> ISceneNodePtr;
	class HrSceneNode;
	typedef std::shared_ptr<HrSceneNode> HrSceneNodePtr;

	class IRenderable;
	class IRenderQueue;
	typedef std::shared_ptr<IRenderQueue> IRenderQueuePtr;
	class HrRenderLayout;
	class HrRenderTechnique;

	class HrGeometryBox;

}


#endif



