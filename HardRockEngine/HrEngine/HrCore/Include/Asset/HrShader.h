#ifndef _HR_SHADER_H_
#define _HR_SHADER_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HR_CORE_API HrShader : public HrResource
	{
	public:
		enum EnumShaderType
		{
			ST_VERTEX_SHADER,
			ST_PIXEL_SHADER,
			ST_GEOMETRY_SHADER,
			ST_DOMAIN_SHADER,
			ST_HULL_SHADER,
			ST_COMPUTE_SHADER
		};
	public:
		HrShader();
		virtual ~HrShader();

		void SetShaderType(EnumShaderType shaderType);
		void SetEntryPoint(std::string strEntryPoint);

		virtual void Bind(HrRender* pRender);
		virtual void UnBind(HrRender* pRender);

		virtual void StreamIn(HrStreamData& streamData);

		virtual void UpdateParams(HrRenderFrameParameters& renderFrameParameters);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

		HrRenderConstantBuffer* AddRenderConstantBuffer();
	protected:
		EnumShaderType m_shaderType;
		std::string m_strEntryPoint;

		std::vector<HrRenderConstantBuffer*> m_vecRenderConstantBuffer;
	};
}

#endif


