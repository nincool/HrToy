#ifndef _HR_MESH_H_
#define _HR_MESH_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"

namespace Hr
{
	class HrSubMesh
	{
	public:
		HrSubMesh();
		~HrSubMesh();

		HrRenderLayout* GetRenderLayout() const;
		void SetMaterial(HrMaterial* pMaterial);
		HrMaterial* GetMaterial() const;

		void SetTexture(HrTexture* pTexture);
		HrTexture* GetTexture() const;
	protected:
		HrRenderLayout* m_pRenderLayout;
		HrMaterial* m_pMaterial;
		HrTexture* m_pTexture;
	};

	class HrMesh : public HrResource
	{
	public:
		HrMesh();
		virtual ~HrMesh();

		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		HrSubMesh* AddSubMesh();
		uint32 GetSubMeshNum();
		HrSubMesh* GetSubMesh(uint32 nIndex);

		void FinishedBuildMesh();
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		std::vector<HrSubMesh*> m_vecSubMesh;
	};
}


#endif



