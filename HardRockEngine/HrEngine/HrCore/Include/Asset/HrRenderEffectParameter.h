#ifndef _HR_RENDEREFFECTCONSTANTBUFFER_H_
#define _HR_RENDEREFFECTCONSTANTBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrUtilTools/Include/HrUtil.h"

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


	enum EnumRenderSemantic
	{
		RS_UNKNOW = 0,
		RS_POSITION = 1,
		RS_NORMAL = 2,
		RS_COLOR = 3,
	};

	//from ogre
	enum EnumRenderParamType
	{
		RPT_WORLDVIEWPROJ_MATRIX,

		RPT_UNKNOWN = 999
	};

	class HR_CORE_API HrRenderParamDefine
	{
	public:
		HrRenderParamDefine(EnumRenderParamType _paramType, const std::string& _strName, EnumRenderEffectDataType _dataType, uint32 _nSize)
			:paramType(_paramType), strName(_strName), dataType(_dataType), nSize(_nSize)
		{
		}

		EnumRenderParamType paramType;
		std::string strName;
		EnumRenderEffectDataType dataType;
		uint32 nSize;

		static std::vector<HrRenderParamDefine> m_s_vecRenderParamDefine;
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

		virtual void BindToCBuffer(HrRenderEffectConstantBuffer* cbuff, uint32_t offset, uint32_t stride);
		virtual void RebindToCBuffer(HrRenderEffectConstantBuffer* cbuff);
		//virtual bool InCBuffer() const
		//{
		//	return false;
		//}
		virtual uint32_t CBufferOffset() const
		{
			return m_nBufferOffset;
		}
		virtual uint32_t Stride() const
		{
			return m_nStride;
		}

	protected:
		EnumRenderEffectDataType m_dataType;
		EnumRenderSemantic m_semantic;

		uint32 m_nBufferOffset;
		uint32 m_nStride;
		Byte* m_pData;

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
			auto pRet = MakeUniquePtr< HrRenderVariableConcrete<T> >();
			pRet->m_dataType = this->m_dataType;
			pRet->m_semantic = this->m_semantic;
			pRet->m_nBufferOffset = this->m_nBufferOffset;
			pRet->m_nStride = this->m_nStride;
			pRet->m_pData = this->m_pData;
			return pRet;
		}

		virtual HrRenderVariable& operator=(T const & value) override
		{
			BOOST_ASSERT(m_pData);
			this->RetriveT() = value;
			return *this;
		}
		
		virtual void Value(T& val) const override
		{
			val = RetriveT();
		}

		virtual void BindToCBuffer(HrRenderEffectConstantBuffer* cbuff, uint32_t offset, uint32_t stride) override
		{
			m_nBufferOffset = offset;
			m_nStride = stride;
			m_pData = cbuff->GetStreamDataPoint() + m_nBufferOffset;
		}
	protected:
		T& RetriveT()
		{
			union  RAW2T
			{
				Byte* pRaw;
				T* t;
			}R2T;
			R2T.pRaw = m_pData;
			return *R2T.t;
		}
		T const & RetriveT() const
		{
			union  RAW2T
			{
				Byte* pRaw;
				T* t;
			}R2T;
			R2T.pRaw = m_pData;
			return *R2T.t;
		}
	};

	template <typename T>
	class HrRenderVariableArray : public HrRenderVariableConcrete<std::vector<T>>
	{
	public:
		virtual HrRenderVariable& operator=(std::vector<T> const& value) override
		{
			for (size_t i = 0; i < value.size(); ++i)
			{
				memcpy(m_pData + i * m_nStride, &value[0], sizeof(value[i]));
			}
			return *this;
		}
		virtual void Value(std::vector<T>& val) const override
		{
			val.resize(m_nSize);
			for (size_t i = 0; i < m_nSize; ++i)
			{
				memcpy(&val[0], m_pData + i * m_nStride, sizeof(val[i]));
			}
		}
	private:
		uint32 m_nSize;
	};

	class HrRenderVariableFloat4x4 : public HrRenderVariableConcrete<float4x4>
	{
	public:
		virtual HrRenderVariable& operator=(const float4x4& value) override;
		virtual void Value(float4x4& val) const override;
	};

	typedef HrRenderVariableConcrete<bool> RenderVariableBool;
	typedef HrRenderVariableConcrete<uint32_t> RenderVariableUInt;
	typedef HrRenderVariableConcrete<int32_t> RenderVariableInt;
	typedef HrRenderVariableConcrete<float> RenderVariableFloat;
	typedef HrRenderVariableConcrete<uint2> RenderVariableUInt2;
	typedef HrRenderVariableConcrete<uint3> RenderVariableUInt3;
	typedef HrRenderVariableConcrete<uint4> RenderVariableUInt4;
	typedef HrRenderVariableConcrete<int2> RenderVariableInt2;
	typedef HrRenderVariableConcrete<int3> RenderVariableInt3;
	typedef HrRenderVariableConcrete<int4> RenderVariableInt4;
	typedef HrRenderVariableConcrete<float2> RenderVariableFloat2;
	typedef HrRenderVariableConcrete<float3> RenderVariableFloat3;
	typedef HrRenderVariableConcrete<float4> RenderVariableFloat4;
	//typedef HrRenderVariableConcrete<SamplerStateObjectPtr> RenderVariableSampler;
	typedef HrRenderVariableConcrete<std::string> RenderVariableString;
	//typedef HrRenderVariableConcrete<ShaderDesc> RenderVariableShader;
	typedef HrRenderVariableArray<bool> RenderVariableBoolArray;
	typedef HrRenderVariableArray<uint32_t> RenderVariableUIntArray;
	typedef HrRenderVariableArray<int32_t> RenderVariableIntArray;
	typedef HrRenderVariableArray<float> RenderVariableFloatArray;
	typedef HrRenderVariableArray<int2> RenderVariableInt2Array;
	typedef HrRenderVariableArray<int3> RenderVariableInt3Array;
	typedef HrRenderVariableArray<int4> RenderVariableInt4Array;
	typedef HrRenderVariableArray<float2> RenderVariableFloat2Array;
	typedef HrRenderVariableArray<float3> RenderVariableFloat3Array;
	typedef HrRenderVariableArray<float4> RenderVariableFloat4Array;


	class HR_CORE_API HrRenderEffectParameter : public boost::noncopyable
	{
	public:
		HrRenderEffectParameter(const std::string& strVarName, size_t nHashName);
		~HrRenderEffectParameter();

		size_t HashName() const { return m_nHashName; }
		const std::string& Name() const { return m_strName; } 

		void ParamInfo(EnumRenderParamType paramType, EnumRenderEffectDataType dataType, uint32 nElements);

		EnumRenderParamType ParamType() { return m_paramType; }
		EnumRenderEffectDataType DataType() { return m_dataType; }
		uint32 Elements() { return m_nElements; }

		void BindConstantBuffer(HrRenderEffectConstantBuffer* pConstantBuffer, uint32 nOffset);
	private:
		EnumRenderParamType m_paramType;
		EnumRenderEffectDataType m_dataType;
		uint32 m_nStride;
		uint32 m_nElements;

		std::string m_strName;
		size_t m_nHashName;

		HrRenderVariable* m_pRenderVariable;

		HrRenderEffectConstantBuffer* m_pBindConstBuffer;
	};

	class HR_CORE_API HrRenderEffectConstantBuffer : public boost::noncopyable
	{
	public:
		HrRenderEffectConstantBuffer(const std::string& strConstBufferName
			, size_t nHashName, size_t nSize);
		~HrRenderEffectConstantBuffer();

		size_t HashName() const { return m_nHashName; }
		const std::string& Name() const { return m_strConstBufferName; }

		Byte* GetStreamOffsetPoint(uint32 nOffset);
		const Byte* GetStreamOffsetPoint(uint32 nOffset) const;
		Byte* GetStreamDataPoint();
		const Byte* GetStreamDataPoint() const;
	private:
		HrStreamData* m_pConstantBufferData;
		HrGraphicsBuffer* m_pConstantBuffer;

		std::string m_strConstBufferName;
		size_t m_nHashName;
		size_t m_nSize;
	};
}

#endif



