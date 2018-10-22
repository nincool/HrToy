#ifndef _HR_MESH_H_
#define _HR_MESH_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrSubMesh 
	{
	public:
		HrSubMesh(int nSubIndex, const HrMeshPtr& pParent, const std::string& strName);
		~HrSubMesh();

		void SetName(const std::string& strName);
		const std::string& GetName();

		void SetMaterial(const HrMaterialPtr& pMaterial);
		const HrMaterialPtr& GetMaterial();

		const HrRenderLayoutPtr& GetRenderLayout();

		void Destroy();
	protected:
		int m_nSubIndex;
		std::string m_strName;

		HrMesh* m_pParentMesh;
		HrRenderLayoutPtr m_pRenderLayout;
		HrMaterialPtr m_pMaterial;
	};

	class HR_CORE_API HrMesh : public HrResource, public std::enable_shared_from_this<HrMesh>
	{
	public:
		HrMesh();
		virtual ~HrMesh();

		static size_t CreateHashName(const std::string& strHashValue);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		const HrSubMeshPtr& AddSubMesh(const std::string& strName);
		uint32 GetSubMeshNum();
		const HrSubMeshPtr& GetSubMesh(uint32 nIndex);

		void FinishedBuildMesh();
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		std::vector<HrSubMeshPtr> m_vecSubMesh;
	};
}


#endif



