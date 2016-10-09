#ifndef _I_SHADER_H_
#define _I_SHADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API IShader
	{
	public:
		enum EnumShaderType
		{
			ST_VERTEX_SHADER,
			ST_PIXEL_SHADER,
		};
		virtual ~IShader(){};
		
		virtual void SetShaderType(EnumShaderType shaderType) = 0;
		//��ں���
		virtual void SetEntryPoint(std::string strEntryPoint) = 0;

		virtual void Bind(HrRender* pRender) = 0;
		virtual void UnBind(HrRender* pRender) = 0;

		//����shader������б���
		virtual void StreamIn(HrStreamData& streamData) = 0;

		virtual void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters) = 0;
	};
}

#endif



