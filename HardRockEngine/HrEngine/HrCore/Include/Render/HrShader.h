#ifndef _HR_SHADER_H_
#define _HR_SHADER_H_

#include "HrCore/Include/Render/IShader.h"

namespace Hr
{
	class HrShader : public IShader
	{
	public:
		enum _SHADER_TYPE_
		{
			ST_VERTEX_SHADER,
			ST_PIXEL_SHADER,
		};

		HrShader(_SHADER_TYPE_ shaderType);
		~HrShader();

		//Èë¿Úº¯Êý
		virtual void SetEntryPoint(std::string strEntryPoint) override;

		virtual void Bind(IRender* pRender) override;
		virtual void UnBind(IRender* pRender) override;
	protected:
		std::string strEntryPoint;
	};
}

#endif