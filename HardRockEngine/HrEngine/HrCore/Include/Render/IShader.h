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
		//入口函数
		virtual void SetEntryPoint(std::string strEntryPoint) = 0;

		virtual void Bind(HrRender* pRender) = 0;
		virtual void UnBind(HrRender* pRender) = 0;

		//传入shader代码进行编译
		virtual void StreamIn(HrStreamData& streamData) = 0;

		virtual void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters) = 0;
	};
}

#endif



