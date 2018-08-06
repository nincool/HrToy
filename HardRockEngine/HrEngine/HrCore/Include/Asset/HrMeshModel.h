#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrMeshRenderable.h"
#include "HrCore/Include/Asset/HrModel.h"

namespace Hr
{
	class HR_CORE_API HrMeshModel : public HrResource
	{
	public:
		static size_t CreateHashName(const std::string& strFullFilePath);
		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;
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

	//struct Vertex1
	//{
	//	float3 position;
	//	float3 normal;
	//	float2 uv;
	//};
	/************************************************************************
	*
	* @Comment£º  A plane is defined in 3D space by the equation
					Ax + By + Cz + D = 0
	*
	* @Author: Hr
	* @Date: [2/28/2017 By Hr]
	*
	************************************************************************/ 
	//class HrGeometryPlane : public HrStaticMeshRenderable
	//{
	//public:
	//	HrGeometryPlane(float fWidth, float fHeight);
	//	~HrGeometryPlane();

	//private:
	//	void GetBuildInPlaneMesh();
	//	void CreatePlaneStaticMesh(const HrMeshPtr& pMesh);

	//public:
	//	Vector3 m_normal;
	//	float m_fWidth;
	//	float m_fHeight;
	//};

	//class HrGeometryBox : public HrStaticMeshRenderable
	//{
	//public:
	//	HrGeometryBox(float fLength);
	//	~HrGeometryBox();

	//private:
	//	void GetBuildInBoxMesh();
	//	void CreateBoxStaticMesh(HrMesh* pMesh);

	//	//void ComputeNormal(Vertex1* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum);
	//private:
	//	float m_fLength;
	//};

	//class HrGeometrySkyBox : public HrModel
	//{
	//public:
	//	enum EnumSkyPlaneSide
	//	{
	//		SPS_FRONT,
	//		SPS_BACK,
	//		SPS_LEFT,
	//		SPS_RIGHT,
	//		SPS_UP,
	//		SPS_BUTTOM
	//	};
	//public:
	//	HrGeometrySkyBox();
	//	~HrGeometrySkyBox();

	//protected:
	//	virtual bool LoadImpl() override;
	//	virtual bool UnloadImpl() override;
	//private:
	//	void GetBuildInSkyBoxMesh();
	//	void CreateSkyBoxStaticMesh(HrMesh* pMesh);
	//	void CreateSkyPlaneVertice(EnumSkyPlaneSide side, Vertex1* pVertice, float fDistance);

	//private:

	//};

	//class HrGeometryFactory
	//{
	//public:
	//	HrGeometryFactory();
	//	~HrGeometryFactory();

	//	HrSceneNodePtr CreatePlane(float fWidth, float fHeight);
	//	HrSceneNode* CreateBox(float fLength);
	//	HrSceneNode* CreateSkyBox();
	//};
}


#endif


