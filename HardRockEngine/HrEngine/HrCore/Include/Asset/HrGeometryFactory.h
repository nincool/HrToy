#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrStaticMeshRenderable.h"
#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Asset/HrPrefabModel.h"

namespace Hr
{
	struct Vertex1
	{
		float3 position;
		float3 normal;
		float2 uv;
	};
	/************************************************************************
	*
	* @Comment£º  A plane is defined in 3D space by the equation
					Ax + By + Cz + D = 0
	*
	* @Author: Hr
	* @Date: [2/28/2017 By Hr]
	*
	************************************************************************/ 
	class HrGeometryPanel : public HrStaticMeshRenderable
	{
	public:
		HrGeometryPanel();
		~HrGeometryPanel();

	private:
		void GetBuildInPanelMesh();
		void CreatePanelStaticMesh(HrMesh* pMesh);

	public:
		Vector3 m_normal;
		REAL m_d;
	};

	class HrGeometryBox : public HrStaticMeshRenderable
	{
	public:
		HrGeometryBox();
		~HrGeometryBox();

	private:
		void GetBuildInBoxMesh();
		void CreateBoxStaticMesh(HrMesh* pMesh);

		void ComputeNormal(Vertex1* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum);
	};

	class HrGeometrySkyBox : public HrPrefabModel
	{
	public:
		enum EnumSkyPlaneSide
		{
			SPS_FRONT,
			SPS_BACK,
			SPS_LEFT,
			SPS_RIGHT,
			SPS_UP,
			SPS_BUTTOM
		};
	public:
		HrGeometrySkyBox();
		~HrGeometrySkyBox();

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	private:
		void GetBuildInSkyBoxMesh();
		void CreateSkyBoxStaticMesh(HrMesh* pMesh);
		void CreateSkyPanelVertice(EnumSkyPlaneSide side, Vertex1* pVertice, float fDistance);

	private:

	};

	class HrGeometryFactory
	{
	public:
		HrGeometryFactory();
		~HrGeometryFactory();

		HrSceneNode* CreatePanel();
		HrSceneNode* CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight);
		HrSceneNode* CreateSkyBox();
	};
}


#endif


