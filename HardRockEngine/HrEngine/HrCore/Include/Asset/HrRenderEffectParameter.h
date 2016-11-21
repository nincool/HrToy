#ifndef _HR_RENDEREFFECTCONSTANTBUFFER_H_
#define _HR_RENDEREFFECTCONSTANTBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	//by definition, will always use either float4 or int4 constant types since that is the fundamental underlying type in assembler. from ogre
	enum EnumRenderEffectDataType
	{
		REDT_FLOAT1 = 1,
		REDT_FLOAT2 = 2,
		REDT_FLOAT3 = 3,
		REDT_FLOAT4 = 4,
		REDT_SAMPLER1D = 5,
		REDT_SAMPLER2D = 6,
		REDT_SAMPLER3D = 7,
		REDT_SAMPLERCUBE = 8,
		REDT_SAMPLERRECT = 9,
		REDT_SAMPLER1DSHADOW = 10,
		REDT_SAMPLER2DSHADOW = 11,
		REDT_SAMPLER2DARRAY = 12,
		REDT_MATRIX_2X2 = 13,
		REDT_MATRIX_2X3 = 14,
		REDT_MATRIX_2X4 = 15,
		REDT_MATRIX_3X2 = 16,
		REDT_MATRIX_3X3 = 17,
		REDT_MATRIX_3X4 = 18,
		REDT_MATRIX_4X2 = 19,
		REDT_MATRIX_4X3 = 20,
		REDT_MATRIX_4X4 = 21,
		REDT_INT1 = 22,
		REDT_INT2 = 23,
		REDT_INT3 = 24,
		REDT_INT4 = 25,
		REDT_SUBROUTINE = 26,
		REDT_DOUBLE1 = 27,
		REDT_DOUBLE2 = 28,
		REDT_DOUBLE3 = 29,
		REDT_DOUBLE4 = 30,
		REDT_MATRIX_DOUBLE_2X2 = 31,
		REDT_MATRIX_DOUBLE_2X3 = 32,
		REDT_MATRIX_DOUBLE_2X4 = 33,
		REDT_MATRIX_DOUBLE_3X2 = 34,
		REDT_MATRIX_DOUBLE_3X3 = 35,
		REDT_MATRIX_DOUBLE_3X4 = 36,
		REDT_MATRIX_DOUBLE_4X2 = 37,
		REDT_MATRIX_DOUBLE_4X3 = 38,
		REDT_MATRIX_DOUBLE_4X4 = 39,
		REDT_UINT1 = 40,
		REDT_UINT2 = 41,
		REDT_UINT3 = 42,
		REDT_UINT4 = 43,
		REDT_BOOL1 = 44,
		REDT_BOOL2 = 45,
		REDT_BOOL3 = 46,
		REDT_BOOL4 = 47,
		REDT_SAMPLER_WRAPPER1D = 48,
		REDT_SAMPLER_WRAPPER2D = 49,
		REDT_SAMPLER_WRAPPER3D = 50,
		REDT_SAMPLER_WRAPPERCUBE = 51,
		REDT_SAMPLER_STATE = 52, //only for hlsl 4.0
		REDT_UNKNOWN = 99

	};

	//from ogre
	enum EnumRenderParamType
	{

		RPT_UNKNOWN = 999
	};

	enum EnumRenderSemantic
	{
		RS_UNKNOW = 0,
		RS_POSITION = 1,
		RS_NORMAL = 2,
		RS_COLOR = 3,
	};


	//from klayge 
	class HR_CORE_API HrRenderVariable
	{
	public:
		HrRenderVariable();
		virtual ~HrRenderVariable();

		virtual std::unique_ptr<HrRenderVariable> Clone() = 0;

		virtual HrRenderVariable& operator=(bool const & value);
		virtual HrRenderVariable& operator=(uint32_t const & value);
		virtual HrRenderVariable& operator=(int32_t const & value);
		virtual HrRenderVariable& operator=(float const & value);
		virtual HrRenderVariable& operator=(uint2 const & value);
		virtual HrRenderVariable& operator=(uint3 const & value);
		virtual HrRenderVariable& operator=(uint4 const & value);
		virtual HrRenderVariable& operator=(int2 const & value);
		virtual HrRenderVariable& operator=(int3 const & value);
		virtual HrRenderVariable& operator=(int4 const & value);
		virtual HrRenderVariable& operator=(float2 const & value);
		virtual HrRenderVariable& operator=(float3 const & value);
		virtual HrRenderVariable& operator=(float4 const & value);
		virtual HrRenderVariable& operator=(float4x4 const & value);
		//virtual HrRenderVariable& operator=(TexturePtr const & value);
		//virtual HrRenderVariable& operator=(TextureSubresource const & value);
		//virtual HrRenderVariable& operator=(SamplerStateObjectPtr const & value);
		//virtual HrRenderVariable& operator=(GraphicsBufferPtr const & value);
		virtual HrRenderVariable& operator=(std::string const & value);
		//virtual HrRenderVariable& operator=(ShaderDesc const & value);
		virtual HrRenderVariable& operator=(std::vector<bool> const & value);
		virtual HrRenderVariable& operator=(std::vector<uint32_t> const & value);
		virtual HrRenderVariable& operator=(std::vector<int32_t> const & value);
		virtual HrRenderVariable& operator=(std::vector<float> const & value);
		virtual HrRenderVariable& operator=(std::vector<uint2> const & value);
		virtual HrRenderVariable& operator=(std::vector<uint3> const & value);
		virtual HrRenderVariable& operator=(std::vector<uint4> const & value);
		virtual HrRenderVariable& operator=(std::vector<int2> const & value);
		virtual HrRenderVariable& operator=(std::vector<int3> const & value);
		virtual HrRenderVariable& operator=(std::vector<int4> const & value);
		virtual HrRenderVariable& operator=(std::vector<float2> const & value);
		virtual HrRenderVariable& operator=(std::vector<float3> const & value);
		virtual HrRenderVariable& operator=(std::vector<float4> const & value);
		virtual HrRenderVariable& operator=(std::vector<float4x4> const & value);

		virtual void Value(bool& val) const;
		virtual void Value(uint32_t& val) const;
		virtual void Value(int32_t& val) const;
		virtual void Value(float& val) const;
		virtual void Value(uint2& val) const;
		virtual void Value(uint3& val) const;
		virtual void Value(uint4& val) const;
		virtual void Value(int2& val) const;
		virtual void Value(int3& val) const;
		virtual void Value(int4& val) const;
		virtual void Value(float2& val) const;
		virtual void Value(float3& val) const;
		virtual void Value(float4& val) const;
		virtual void Value(float4x4& val) const;
		//virtual void Value(TexturePtr& val) const;
		//virtual void Value(TextureSubresource& val) const;
		//virtual void Value(SamplerStateObjectPtr& val) const;
		//virtual void Value(GraphicsBufferPtr& value) const;
		virtual void Value(std::string& val) const;
		//virtual void Value(ShaderDesc& val) const;
		virtual void Value(std::vector<bool>& val) const;
		virtual void Value(std::vector<uint32_t>& val) const;
		virtual void Value(std::vector<int32_t>& val) const;
		virtual void Value(std::vector<float>& val) const;
		virtual void Value(std::vector<uint2>& val) const;
		virtual void Value(std::vector<uint3>& val) const;
		virtual void Value(std::vector<uint4>& val) const;
		virtual void Value(std::vector<int2>& val) const;
		virtual void Value(std::vector<int3>& val) const;
		virtual void Value(std::vector<int4>& val) const;
		virtual void Value(std::vector<float2>& val) const;
		virtual void Value(std::vector<float3>& val) const;
		virtual void Value(std::vector<float4>& val) const;
		virtual void Value(std::vector<float4x4>& val) const;

		virtual void BindToCBuffer(HrRenderEffectConstantBuffer& cbuff, uint32_t offset, uint32_t stride);
		virtual void RebindToCBuffer(HrRenderEffectConstantBuffer& cbuff);
		//virtual bool InCBuffer() const
		//{
		//	return false;
		//}
		virtual uint32_t CBufferOffset() const
		{
			return m_nInBufferOffset;
		}
		virtual uint32_t Stride() const
		{
			return m_nStride;
		}

	protected:
		EnumRenderEffectDataType m_dataType;
		EnumRenderSemantic m_semantic;

		uint32 m_nInBufferOffset;
		uint32 m_nStride;
	};

	template <typename T>
	class HrRenderVariableConcrete : public HrRenderVariable
	{
	public:
		HrRenderVariableConcrete()
		{
		}
		virtual ~HrRenderVariableConcrete()
		{
		}

		std::unique_ptr<HrRenderVariable> Clone() override
		{
			auto pRet = MakeUniquePtr < HrRenderVariableConcrete<T>>();
			
			return pRet;
		}

		virtual HrRenderVariable& operator=(T const & value) override
		{
		}
		
		virtual void Value(T& val) const override
		{

		}

		virtual void BindToCBuffer(HrRenderEffectConstantBuffer& cbuff, uint32_t offset, uint32_t stride) override
		{

		}
	protected:
		T& RetriveT()
		{
			union  RAW2T
			{
				byte_t* pRaw;
				T* t;
			}R2T;
			R2T.pRaw = m_pData;
			return *R2T.t;
		}
		T const & RetriveT() const
		{
			union  RAW2T
			{
				byte_t* pRaw;
				T* t;
			}R2T;
			R2T.pRaw = m_pData;
			return *R2T.t;
		}
	protected:
		byte_t* m_pData;
	};

	class HR_CORE_API HrRenderEffectParameter : public boost::noncopyable
	{
	public:
		HrRenderEffectParameter(const std::string& strVarName, size_t nHashName);
		~HrRenderEffectParameter();

		size_t HashName() const { return m_nHashName; }
		const std::string& Name() const { return m_strName; } 
	private:
		EnumRenderEffectDataType m_paramType;

		std::string m_strName;
		size_t m_nHashName;

		HrRenderEffectConstantBuffer* m_pAttachConstBuffer;
	};

	class HR_CORE_API HrRenderEffectConstantBuffer : public boost::noncopyable
	{
	public:
		HrRenderEffectConstantBuffer(const std::string& strConstBufferName, size_t nHashName);
		~HrRenderEffectConstantBuffer();

		size_t HashName() const { return m_nHashName; }
		const std::string& Name() const { return m_strConstBufferName; }

		
	private:
		HrStreamData* m_pConstantBufferData;

		HrGraphicsBuffer* m_pConstantBuffer;

		std::string m_strConstBufferName;
		size_t m_nHashName;
	};
}

#endif



