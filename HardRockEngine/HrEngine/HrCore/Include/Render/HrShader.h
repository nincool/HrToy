#ifndef _HR_SHADER_H_
#define _HR_SHADER_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HR_CORE_API HrShader 
	{
	public:
		enum EnumShaderType
		{
			ST_VERTEX_SHADER,
			ST_PIXEL_SHADER,
			ST_GEOMETRY_SHADER,
			ST_DOMAIN_SHADER,
			ST_HULL_SHADER,
			ST_COMPUTE_SHADER,

			ST_NUMSHADERTYPES
		};
	public:
		HrShader();
		virtual ~HrShader();

		virtual void Bind(HrRender* pRender) = 0;
		virtual void UnBind(HrRender* pRender) = 0;

		virtual void StreamIn(HrStreamData& streamBuffer, std::string& strFile, EnumShaderType shaderType) = 0;

		virtual void UpdateParams(HrRenderFrameParameters& renderFrameParameters) {};
	protected:
		HrRenderConstantBuffer* AddRenderConstantBuffer();
	protected:
		EnumShaderType m_shaderType;

		std::vector<HrRenderConstantBuffer*> m_vecRenderConstantBuffer;
	};
}

#endif


