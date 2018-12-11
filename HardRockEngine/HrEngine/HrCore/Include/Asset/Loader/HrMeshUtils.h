#ifndef _HR_MESHUTILS_H_
#define _HR_MESHUTILS_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrMeshUtils
	{
	public:
		static AABBox ComputeAABB(const std::vector<Vector3>& vecVertexPos);
		static void ComputeExtrameDistanceAlongDir(const Vector3& vDir, const std::vector<Vector3>& vecVertices, uint32& nMax, uint32& nMin);

	};
}

#endif
