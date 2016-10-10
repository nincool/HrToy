#ifndef _HR_SHADER_H_
#define _HR_SHADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrShader
	{
	public:
		enum EnumShaderType
		{
			ST_VERTEX_SHADER,
			ST_PIXEL_SHADER,
		};
	public:
		HrShader();
		virtual ~HrShader();

		virtual void SetShaderType(EnumShaderType shaderType);
		//Èë¿Úº¯Êý
		virtual void SetEntryPoint(std::string strEntryPoint);

		virtual void Bind(HrRender* pRender);
		virtual void UnBind(HrRender* pRender);

		virtual void StreamIn(HrStreamData& streamData);

		virtual void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters);

	protected:
		HrRenderConstantBuffer* AddRenderConstantBuffer();

	protected:
		EnumShaderType m_shaderType;
		std::string m_strEntryPoint;

		std::vector<HrRenderConstantBuffer*> m_vecRenderConstantBuffer;
	};
}

#endif


