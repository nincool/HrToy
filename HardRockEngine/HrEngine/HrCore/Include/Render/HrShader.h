#ifndef _HR_SHADER_H_
#define _HR_SHADER_H_

#include "HrCore/Include/Render/IShader.h"

namespace Hr
{
	class HR_CORE_API HrShader : public IShader
	{
	public:
		HrShader();
		virtual ~HrShader();

		virtual void SetShaderType(EnumShaderType shaderType) override;
		//Èë¿Úº¯Êý
		virtual void SetEntryPoint(std::string strEntryPoint) override;

		virtual void Bind(HrRender* pRender) override;
		virtual void UnBind(HrRender* pRender) override;

		virtual void StreamIn(HrStreamData& streamData) override;

		virtual void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters) override;
	protected:
		HrRenderConstantBuffer* AddRenderConstantBuffer();
	protected:
		EnumShaderType m_shaderType;
		std::string m_strEntryPoint;

		std::vector<HrRenderConstantBuffer*> m_vecRenderConstantBuffer;
	};
}

#endif


