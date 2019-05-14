#ifndef _HR_SKYBOX_H_
#define _HR_SKYBOX_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrMeshRenderable.h"

namespace Hr
{
	class HR_CORE_API HrSkyBox : public HrStaticMeshRenderable
	{
	public:
		HrSkyBox(const HrSubMeshPtr& pSubMesh);
		~HrSkyBox();

		virtual void OnRenderBegin() override;
		virtual void OnRenderEnd() override;

		void SetCubeMap(const HrTexturePtr& pCubeMap);

	private:
		HrRenderEffectParameterPtr m_pEffectParamCubeMap;
		HrRenderEffectParameterPtr m_pEffectParamWVP;
	};
}

#endif



