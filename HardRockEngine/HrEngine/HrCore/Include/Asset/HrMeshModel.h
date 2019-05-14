#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrMeshRenderable.h"

namespace Hr
{
	struct SVertexStruct_P
	{
		SVertexStruct_P();
		float3 m_position;
		static std::vector<HrVertexElement> m_s_vecVertexElement_P;
	};

	struct SVertexStruct_P_UV : public SVertexStruct_P
	{
		SVertexStruct_P_UV();
		float2 m_tex;
		static std::vector<HrVertexElement> m_s_vecVertexElement_P_UV;
	};

	struct SVertexStruct_P_N : public SVertexStruct_P
	{
		SVertexStruct_P_N();
		float3 m_normal;
		static std::vector<HrVertexElement> m_s_vecVertexElement_P_N;
	};

	struct SVertexStruct_P_N_UV : public SVertexStruct_P_N
	{
		SVertexStruct_P_N_UV();
		float2 m_tex;
		static std::vector<HrVertexElement> m_s_vecVertexElement_P_N_UV;
	};

	struct SVertexStruct_P_T_N_UV
	{
		SVertexStruct_P_T_N_UV();
		float3 m_position;
		float3 m_tangent;
		float3 m_normal;
		float2 m_tex;
		static std::vector<HrVertexElement> m_s_vecVertexElement_P_T_N_UV;
	};

	class HrQuad_P_UV
	{
	public:
		SVertexStruct_P_UV m_vecVertices[4];
		HrMeshPtr m_pMesh;
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

	class HR_CORE_API HrMeshModelQuad_P_UV : public HrMeshModel
	{
	public:
		HrMeshModelQuad_P_UV(float fWidth, float fHeight);
		~HrMeshModelQuad_P_UV();

	private:
		void CreateQuadMesh();

	private:
		float m_fWidth;
		float m_fHeight;
	};

	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////


	class HR_CORE_API HrMeshModelQuadPN : public HrMeshModel
	{
	public:
		HrMeshModelQuadPN(float fWidth, float fHeight);
		~HrMeshModelQuadPN();

	private:
		void CreateQuadMesh();

	private:
		float m_fWidth;
		float m_fHeight;
	};

	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////

	class HR_CORE_API HrMeshModelQuadPNC : public HrMeshModel
	{
	public:
		HrMeshModelQuadPNC(float fWidth, float fHeight);
		~HrMeshModelQuadPNC();

	private:
		void CreateQuadMesh();

	private:
		float m_fWidth;
		float m_fHeight;
	};


	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////

	class HR_CORE_API HrMeshModelSpherePTNUV : public HrMeshModel
	{
	public:
		HrMeshModelSpherePTNUV(float radius, int slice, int stack);

	private:
		void CreateSphereMesh(float radius, int slice, int stack);
	};

	//////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////

	class HrMeshModelGrid : public HrMeshModel
	{
	public:
		HrMeshModelGrid(float fSteps, float fStepLong);
		~HrMeshModelGrid();

	protected:
		struct SGridVertex 
		{
			float3 position;
			SGridVertex()
			{
				position = Vector3::Zero();
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

	class HR_CORE_API HrMeshModelObject : public HrMeshModel
	{
	public:
		HrMeshModelObject();
		~HrMeshModelObject();

		const HrModelLoaderPtr& GetModelLoader();
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		HrModelLoaderPtr m_pModelLoader;
	};

	////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////


}


#endif


