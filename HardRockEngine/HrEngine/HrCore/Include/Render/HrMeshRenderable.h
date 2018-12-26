#ifndef _HR_MESHRENDERABLE_H_
#define _HR_MESHRENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HR_CORE_API HrStaticMeshRenderable : public HrRenderable
	{
	public:
		HrStaticMeshRenderable(const HrSubMeshPtr& pSubMesh);
		~HrStaticMeshRenderable();

		//virtual const HrRenderLayoutPtr& GetRenderLayout() override;

	protected:

	};

	////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////

	//class HrSkinnedMeshRenderable : public HrRenderable
	//{
	//public:
	//	HrSkinnedMeshRenderable();
	//	~HrSkinnedMeshRenderable();

	//	virtual const HrRenderLayoutPtr& GetRenderLayout() override;

	//protected:

	//};
}


#endif
