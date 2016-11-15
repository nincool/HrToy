#ifndef _HR_MESH_H_
#define _HR_MESH_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HrSubMesh
	{
		HrRenderLayout* m_pRenderLayout;
	};

	class HrMesh : public HrResource
	{
	public:
		HrMesh();
		virtual ~HrMesh();

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		virtual void Load() override;
		virtual void Unload() override;

		HrRenderLayout* GetRenderLayout();
	protected:
		HrRenderLayout* m_pRenderLayout;


	};
}


#endif



