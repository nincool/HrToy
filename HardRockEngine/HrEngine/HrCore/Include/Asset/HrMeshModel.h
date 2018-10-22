#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrMeshRenderable.h"
#include "HrCore/Include/Asset/HrModel.h"

namespace Hr
{
	struct SVertexStructP
	{
		SVertexStructP();
		float3 m_position;
		static std::vector<HrVertexElement> m_s_vecVertexElementP;
	};

	struct SVertexStructPC : public SVertexStructP
	{
		SVertexStructPC();
		float2 m_tex;
		static std::vector<HrVertexElement> m_s_vecVertexElementPC;
	};

	struct SVertexStructPN : public SVertexStructP
	{
		SVertexStructPN();
		float3 m_normal;
		static std::vector<HrVertexElement> m_s_vecVertexElementPN;
	};

	struct SVertexStructPNC : public SVertexStructPN
	{
		SVertexStructPNC();
		float2 m_tex;
		static std::vector<HrVertexElement> m_s_vecVertexElementPNC;
	};

	class HR_CORE_API HrMeshModel : public HrResource
	{
	public:
		static size_t CreateHashName(const std::string& strFullFilePath);
		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath = "") override;
		const HrMeshPtr& GetMesh() const;
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		HrMeshPtr m_pMesh;

		//Mapping the submesh and material; 
		//the key is name of a submesh and value is the material
		std::unordered_map<std::string, HrMaterialPtr> m_mapMaterials;
	};

	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////
	
	class HR_CORE_API HrMeshModelQuadP : public HrMeshModel
	{
	public:
		HrMeshModelQuadP(float fWidth, float fHeight);
		~HrMeshModelQuadP();

	private:
		void CreateQuadMesh();

	private:
		float m_fWidth;
		float m_fHeight;
	};

	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////

	class HrMeshModelGrid : public HrMeshModel
	{
	public:
		HrMeshModelGrid();
		~HrMeshModelGrid();

	protected:
		struct SGridVertex 
		{
			float3 position;
			float3 normal;
			SGridVertex()
			{
				position = Vector3::Zero();
				normal = Vector3::Zero();
			}
		};

		virtual bool LoadImpl() override;
	private:
		void CreateGridMesh();
		
	private:
		uint16 m_nSteps;
		float m_fStepLong;
	};

	////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////

	class HrMeshModelObject : public HrMeshModel
	{
	public:
		HrMeshModelObject();
		~HrMeshModelObject();

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	};
}


#endif


