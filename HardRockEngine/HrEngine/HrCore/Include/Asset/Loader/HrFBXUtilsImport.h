#ifndef _HR_FBXUTILSIMPORT_H_
#define _HR_FBXUTILSIMPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"
#include "fbxsdk.h"



namespace Hr
{
	class HrFBXDataConverter
	{
	public:
		static Vector3 ConvertPos(const fbxsdk::FbxVector4 vPos);
		static Vector3 ConvertDir(const fbxsdk::FbxVector4 vDir);
	};
}





#endif
