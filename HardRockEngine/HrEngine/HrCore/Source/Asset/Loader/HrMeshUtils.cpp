#include "Asset/Loader/HrMeshUtils.h"

using namespace Hr;

AABBox HrMeshUtils::ComputeAABB(const std::vector<Vector3>& vecVertexPos)
{
	uint32 nMaxIndex = 0, nMinIndex = 0;
	Vector3 v3MinPoint, v3MaxPoint;
	ComputeExtrameDistanceAlongDir(Vector3(1, 0, 0), vecVertexPos, nMaxIndex, nMinIndex);
	v3MinPoint.x() = vecVertexPos[nMinIndex].x();
	v3MaxPoint.x() = vecVertexPos[nMaxIndex].x();

	ComputeExtrameDistanceAlongDir(Vector3(0, 1, 0), vecVertexPos, nMaxIndex, nMinIndex);
	v3MinPoint.y() = vecVertexPos[nMinIndex].y();
	v3MaxPoint.y() = vecVertexPos[nMaxIndex].y();

	ComputeExtrameDistanceAlongDir(Vector3(0, 0, 1), vecVertexPos, nMaxIndex, nMinIndex);
	v3MinPoint.z() = vecVertexPos[nMinIndex].z();
	v3MaxPoint.z() = vecVertexPos[nMaxIndex].z();

	return AABBox(v3MinPoint, v3MaxPoint);
}

void HrMeshUtils::ComputeExtrameDistanceAlongDir(const Vector3& vDir, const std::vector<Vector3>& vecVertices, uint32& nMax, uint32& nMin)
{
	float fMaxProj = -FLT_MAX, fMinProj = FLT_MAX;
	for (size_t i = 0; i < vecVertices.size(); ++i)
	{
		float fProjection = HrMath::Dot(vecVertices[i], vDir);

		if (fProjection > fMaxProj)
		{
			fMaxProj = fProjection;
			nMax = i;
		}

		if (fProjection < fMinProj)
		{
			fMinProj = fMinProj;
			nMin = i;
		}
	}
}
