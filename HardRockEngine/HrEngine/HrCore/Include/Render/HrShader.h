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

		virtual void SetShaderType(_SHADER_TYPE_ shaderType) override;
		//Èë¿Úº¯Êý
		virtual void SetEntryPoint(std::string strEntryPoint) override;

		virtual void Bind(IRender* pRender) override;
		virtual void UnBind(IRender* pRender) override;

		virtual void StreamIn(HrStreamData& streamData) override;

		virtual void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters) override;
	protected:
		HrRenderConstantBuffer* AddRenderConstantBuffer();
	protected:
		_SHADER_TYPE_ m_shaderType;
		std::string m_strEntryPoint;

		std::vector<HrRenderConstantBuffer*> m_vecRenderConstantBuffer;
	};
}

#endif


