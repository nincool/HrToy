#include "HrCore/Include/Render/HrShader.h"
#include "HrCore/Include/Render/HrRenderConstantBuffer.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrShader::HrShader()
{
	m_shaderType = ST_VERTEX_SHADER;
}

HrShader::~HrShader()
{
	for (auto& item : m_vecRenderConstantBuffer)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderConstantBuffer.clear();
}

HrRenderConstantBuffer* HrShader::AddRenderConstantBuffer()
{
	HrRenderConstantBuffer* pRenderConstantBuffer = HR_NEW HrRenderConstantBuffer();
	m_vecRenderConstantBuffer.push_back(pRenderConstantBuffer);

	return pRenderConstantBuffer;
}

