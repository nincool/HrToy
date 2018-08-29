#ifndef _HR_ENGINE_H_
#define _HR_ENGINE_H_

#include "HrCore/Include/Kernel/HrLog.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrCoreComponentEvent.h"
#include "HrCore/Include/Kernel/HrCoreComponentRender.h"
#include "HrCore/Include/Kernel/HrCoreComponentScene.h"
#include "HrCore/Include/Kernel/HrCoreComponentWin.h"
#include "HrCore/Include/Kernel/HrCoreComponentResource.h"

#include "HrCore/Include/Event/HrEventDispatcher.h"
#include "HrCore/Include/Event/HrEventListener.h"

#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrSceneObjectFactory.h"
#include "HrCore/Include/Asset/HrMeshModel.h"
#include "HrCore/Include/Asset/HrModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrMaterial.h"
#include "HrCore/Include/Asset/HrStreamData.h"

#include "HrCore/Include/Scene/HrTransform.h"
#include "HrCore/Include/Scene/HrSceneImported.h"
#include "HrCore/Include/Scene/HrSceneNode.h"
#include "HrCore/Include/Scene/HrSceneObject.h"

#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrScheduler.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"

#include "HrCore/Include/Render/HrRenderable.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFrame.h"

#include "HrUtilTools/Include/HrStringUtil.h"

#ifdef HR_PLATFORM_WIN32
#include "HrCore/Include/Platform/AppWin/HrWindowWin.h"
#endif // HR_PLATFORM_WIN32
#include "HrUtilTools/Include/HrUtil.h"

#endif

