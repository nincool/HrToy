#include "Asset/Loader/HrFBXUtilsImport.h"

using namespace Hr;

Vector3 HrFBXDataConverter::ConvertPos(const fbxsdk::FbxVector4 vPos)
{
	// flip Y, then the right-handed axis system is converted to LHS
	return Vector3(vPos[0], -vPos[1], vPos[2]);
}

Vector3 HrFBXDataConverter::ConvertDir(const fbxsdk::FbxVector4 vDir)
{
	return Vector3(vDir[0], -vDir[1], vDir[2]);
}
