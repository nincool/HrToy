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

		virtual void Bind(const HrRenderPtr& pRender) = 0;
		virtual void UnBind(const HrRenderPtr& pRender) = 0;

		virtual void StreamIn(const HrStreamDataPtr& streamBuffer, const std::string& strFile, const std::string& strName, EnumShaderType shaderType) = 0;

		EnumShaderType ShaderType() { return m_shaderType; }
		std::string& Name() { return m_strName; }
		size_t HashName() { return m_nHashName; }

		virtual void BindRenderParameter(std::vector<HrRenderEffectParameterPtr>& vecRenderParameter
			, std::vector<HrRenderEffectStructParameterPtr>& vecRenderStructParameter
			, std::vector<HrRenderEffectConstantBufferPtr>& vecRenderConstBuffer);
		void GetBindRenderParameter(std::vector<HrRenderEffectParameterPtr>& vecRenderParameter, std::vector<HrRenderEffectStructParameterPtr>& vecRenderStruct);
	protected:
		virtual void BindRenderParameterImpl() = 0;

	protected:
		EnumShaderType m_shaderType;
		std::string m_strName;
		size_t m_nHashName;

		std::vector<HrRenderEffectParameterPtr> m_vecBindRenderParameter;
		//���������⣬Ӧ�ø��ݲ�ͬ��shader�󶨵Ĳ�ͬ��ConstantBuffer������
		std::vector<HrRenderEffectStructParameterPtr> m_vecBindRenderStructParameter;
		std::vector<HrRenderEffectConstantBufferPtr> m_vecBindRenderConstantBuffer;
	};
}

#endif


