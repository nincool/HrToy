#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrModelLoader::HrModelLoader()
{

}

HrModelLoader::~HrModelLoader()
{

}

void HrModelLoader::Load(std::string& strFile)
{
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
	if (strSuffix == "fbx")
	{
		std::shared_ptr<HrFBXLoader> pFBXLoader = MakeSharedPtr<HrFBXLoader>();
		pFBXLoader->Load(strFile, m_vecVertexBuffer, m_vecIndexBuffer);
	}

	
}

