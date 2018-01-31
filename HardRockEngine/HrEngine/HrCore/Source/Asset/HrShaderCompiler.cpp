#include "Asset/HrShaderCompiler.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"

using namespace Hr;

HrShaderCompiler::HrShaderCompiler(const std::string& strFileName)
{
	m_strFileName = strFileName;
	m_pStreamData = HrFileUtils::Instance()->GetFileData(m_strFileName);
}

HrShaderCompiler::~HrShaderCompiler()
{
}


