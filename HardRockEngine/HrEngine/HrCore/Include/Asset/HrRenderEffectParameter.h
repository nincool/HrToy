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
		REDT_FLOAT2,
		REDT_FLOAT3,
		REDT_FLOAT4,
		REDT_TEXTURE1D,
		REDT_TEXTURE2D,
		REDT_TEXTURE3D,
		REDT_SAMPLER1D,
		REDT_SAMPLER2D,
		REDT_SAMPLER3D,
		REDT_SAMPLERCUBE,
		REDT_SAMPLERRECT,
		REDT_SAMPLER1DSHADOW,
		REDT_SAMPLER2DSHADOW,
		REDT_SAMPLER2DARRAY,
		REDT_MATRIX_2X2,
		REDT_MATRIX_2X3,
		REDT_MATRIX_2X4,
		REDT_MATRIX_3X2,
		REDT_MATRIX_3X3,
		REDT_MATRIX_3X4,
		REDT_MATRIX_4X2,
		REDT_MATRIX_4X3,
		REDT_MATRIX_4X4,
		REDT_INT1,
		REDT_INT2,
		REDT_INT3,
		REDT_INT4,
		REDT_SUBROUTINE,
		REDT_DOUBLE1,
		REDT_DOUBLE2,
		REDT_DOUBLE3,
		REDT_DOUBLE4,
		//REDT_MATRIX_DOUBLE_2X2,
		//REDT_MATRIX_DOUBLE_2X3,
		//REDT_MATRIX_DOUBLE_2X4,
		//REDT_MATRIX_DOUBLE_3X2,
		//REDT_MATRIX_DOUBLE_3X3,
		//REDT_MATRIX_DOUBLE_3X4,
		//REDT_MATRIX_DOUBLE_4X2,
		//REDT_MATRIX_DOUBLE_4X3,
		//REDT_MATRIX_DOUBLE_4X4,
		REDT_UINT1,
		REDT_UINT2,
		REDT_UINT3,
		REDT_UINT4,
		REDT_BOOL1,
		REDT_BOOL2,
		REDT_BOOL3,
		REDT_BOOL4,
		REDT_SAMPLER_WRAPPER1D,
		REDT_SAMPLER_WRAPPER2D,
		REDT_SAMPLER_WRAPPER3D,
		REDT_SAMPLER_WRAPPERCUBE,
		REDT_SAMPLER_STATE, //only for hlsl 4.0
		REDT_UNKNOWN = 99
	};

	//from ogre
	enum EnumRenderParamType
	{
		RPT_WORLD_MATRIX,
		RPT_INVERSE_WROLD_MATRIX,
		RPT_TRANSPOSE_WORLD_MATRIX,
		RPT_INVERSE_TRANSPOSE_WORLD_MATRIX,
		RPT_VIEW_PROJ_MATRIX,
		RPT_WORLD_VIEW_PROJ_MATRIX,

		//Camera
		RPT_CAMERA_POSITION,

		//灯光属性
		RPT_AMBIENT_COLOR,

		RPT_LIGHTS_NUM,
		//方向光
		RPT_DIRECTIONAL_LIGHT_DIRECTION,
		RPT_DIRECTIONAL_LIGHT_COLOR,
		//点光源
		RPT_POINT_LIGHT_POSITION,
		RPT_POINT_LIGHT_COLOR,
		RPT_POINT_LIGHT_ATTENUATION,

		//材质属性
		RPT_MATERIAL_GLOSSINESS,
		RPT_MATERIAL_ALBEDO,
		RPT_MATERIAL_REFLECTIVE,
	

		//纹理
		RPT_TEXTURE,
		RPT_SAMPLER,

		//Fog
		RPT_FOG_COLOR,
		RPT_FOG_START,
		RPT_FOG_RANGE,

		PRT_CUSTOM,

		RPT_UNKNOWN = 999
	};

	class HR_CORE_API HrRenderParamDefine
	{
	public:
		HrRenderParamDefine(EnumRenderParamType _paramType
			, const std::string& _strName
			, EnumRenderEffectDataType _dataType
			, uint32 _nElementCount
			, uint32 _nStride)
			:paramType(_paramType), strName(_strName), dataType(_dataType), nElementCount(_nElementCount), nStride(_nStride)
		{
		}

		EnumRenderParamType paramType;
		std::string strName;
		EnumRenderEffectDataType dataType;
		uint32 nElementCount;
		uint32 nStride;

		static std::vector<HrRenderParamDefine> m_s_vecRenderParamDefine;
		static HrRenderParamDefine* GetRenderParamDefineByType(EnumRenderParamType rpt);
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
		virtual HrRenderVariable& operator=(const HrTexture* pTexture);
		//virtual HrRenderVariable& operator=(TexturePtr const & value);
		//virtual HrRenderVariable& operator=(TextureSubresource const & value);
		virtual HrRenderVariable& operator=(const HrSamplerState* pSamplerState);
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
		virtual void Value(HrTexture*& val) const;
		virtual void Value(HrSamplerState*& val) const;
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

		virtual void BindToCBuffer(const HrRenderEffectConstantBufferPtr& cbuff, uint32_t offset, uint32_t stride, uint32 nMemorySize);
		virtual void RebindToCBuffer(const HrRenderEffectConstantBufferPtr& cbuff);
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

		uint32 m_nBufferOffset;
		uint32 m_nStride;
		uint32 m_nArraySize;
		uint32 m_nMemorySize;
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
			auto pRet = HrMakeUniquePtr< HrRenderVariableConcrete<T> >();
			pRet->m_dataType = this->m_dataType;
			pRet->m_nBufferOffset = this->m_nBufferOffset;
			pRet->m_nMemorySize = this->m_nMemorySize;
			pRet->m_nArraySize = this->m_nArraySize;
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

		virtual void BindToCBuffer(const HrRenderEffectConstantBufferPtr& cbuff, uint32_t offset, uint32_t stride, uint32 nMemorySize) override
		{
			m_nBufferOffset = offset;
			m_nStride = stride;
			m_nMemorySize = nMemorySize;
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
				memcpy(m_pData + i * m_nStride, &value[i], sizeof(value[i]));
			}
			//memcpy(m_pData, &value[0], m_nStride)
			return *this;
		}
		virtual void Value(std::vector<T>& val) const override
		{
			val.resize(m_nArraySize);
			for (size_t i = 0; i < m_nArraySize; ++i)
			{
				memcpy(&val[i], m_pData + i * m_nStride, sizeof(val[i]));
			}
		}
	};

	class HrRenderVariableFloat4x4 : public HrRenderVariableConcrete<float4x4>
	{
	public:
		virtual HrRenderVariable& operator=(const float4x4& value) override;
		virtual void Value(float4x4& val) const override;
	};

	class HrRenderVariableFloat4x4Array : public HrRenderVariableConcrete<std::vector<float4x4> >
	{
	public:
		HrRenderVariableFloat4x4Array();
		virtual HrRenderVariable& operator=(const std::vector<float4x4>& value) override;
		virtual void Value(std::vector<float4x4>& val) const override;

	};

	class HrRenderVariableTexture : public HrRenderVariable
	{
	public:
		HrRenderVariableTexture();
		~HrRenderVariableTexture();

		virtual HrRenderVariable& operator=(const HrTexture* pTexture) override;

		virtual std::unique_ptr<HrRenderVariable> Clone() override
		{
			auto pRet = HrMakeUniquePtr< HrRenderVariableTexture >();

			return std::move(pRet);
		}

		virtual void Value(HrTexture*& val) const override;
	protected:
		HrTexture* m_pTexture;
	};

	class HrRenderVariableSamplerState :public HrRenderVariable
	{
	public:
		HrRenderVariableSamplerState();
		~HrRenderVariableSamplerState();

		virtual HrRenderVariable& operator=(const HrSamplerState* pSamplerState) override;
		
		virtual std::unique_ptr<HrRenderVariable> Clone() override
		{
			auto pRet = HrMakeUniquePtr< HrRenderVariableSamplerState >();

			return std::move(pRet);
		}

		virtual void Value(HrSamplerState*& val) const override;
	protected:
		HrSamplerStatePtr m_pSamplerState;
	};

	typedef HrRenderVariableConcrete<bool> HrRenderVariableBool;
	typedef HrRenderVariableConcrete<uint32_t> HrRenderVariableUInt;
	typedef HrRenderVariableConcrete<int32_t> HrRenderVariableInt;
	typedef HrRenderVariableConcrete<float> HrRenderVariableFloat;
	typedef HrRenderVariableConcrete<uint2> HrRenderVariableUInt2;
	typedef HrRenderVariableConcrete<uint3> HrRenderVariableUInt3;
	typedef HrRenderVariableConcrete<uint4> HrRenderVariableUInt4;
	typedef HrRenderVariableConcrete<int2> HrRenderVariableInt2;
	typedef HrRenderVariableConcrete<int3> HrRenderVariableInt3;
	typedef HrRenderVariableConcrete<int4> HrRenderVariableInt4;
	typedef HrRenderVariableConcrete<float2> HrRenderVariableFloat2;
	typedef HrRenderVariableConcrete<float3> HrRenderVariableFloat3;
	typedef HrRenderVariableConcrete<float4> HrRenderVariableFloat4;
	//typedef HrRenderVariableConcrete<SamplerStateObjectPtr> RenderVariableSampler;
	typedef HrRenderVariableConcrete<std::string> HrRenderVariableString;
	//typedef HrRenderVariableConcrete<ShaderDesc> RenderVariableShader;
	typedef HrRenderVariableArray<bool> HrRenderVariableBoolArray;
	typedef HrRenderVariableArray<uint32_t> HrRenderVariableUIntArray;
	typedef HrRenderVariableArray<int32_t> HrRenderVariableIntArray;
	typedef HrRenderVariableArray<float> HrRenderVariableFloatArray;
	typedef HrRenderVariableArray<int2> HrRenderVariableInt2Array;
	typedef HrRenderVariableArray<int3> HrRenderVariableInt3Array;
	typedef HrRenderVariableArray<int4> HrRenderVariableInt4Array;
	typedef HrRenderVariableArray<float2> HrRenderVariableFloat2Array;
	typedef HrRenderVariableArray<float3> HrRenderVariableFloat3Array;
	typedef HrRenderVariableArray<float4> HrRenderVariableFloat4Array;


	class HR_CORE_API HrRenderEffectParameter : public boost::noncopyable
	{
	public:
		enum EnumRenderEffectParamBindType
		{
			REPBT_UNKNOWN,
			REPBT_CONSTBUFFER,
			REPBT_RESOURCE,
		};
	public:
		HrRenderEffectParameter(const std::string& strVarName, size_t nHashName);
		~HrRenderEffectParameter();

		template <typename T>
		bool operator==(const T& value)
		{
			T val;
			m_pRenderVariable->Value(val);
			bool bvalue = (val == value);
			return val == value;
		}

		template <typename T>
		HrRenderEffectParameter& operator=(const T& value)
		{
			m_pRenderVariable->operator=(value);
			if (m_pBindConstBuffer != nullptr)
				m_pBindConstBuffer->Dirty(true);
			 
			return *this;
		}

		template <typename T>
		void Value(T& val) const
		{
			m_pRenderVariable->Value(val);
		}

		size_t HashName() const { return m_nHashName; }
		const std::string& Name() const { return m_strName; } 

		void ParamInfo(EnumRenderParamType paramType
			, EnumRenderEffectDataType dataType
			, EnumRenderEffectParamBindType bindType
			, uint32 nStride, uint32 nArraySize);

		EnumRenderParamType ParamType() { return m_paramType; }
		EnumRenderEffectDataType DataType() { return m_dataType; }
		EnumRenderEffectParamBindType BindType() { return m_bindType; }
		uint32 ArraySize() { return m_nArraySize; }
		uint32 MemorySize() { return m_nMemorySize; }

		void BindConstantBuffer(const HrRenderEffectConstantBufferPtr& pConstantBuffer, uint32 nOffset);
		const HrRenderEffectConstantBufferPtr& GetBindConstantBuffer() const { return m_pBindConstBuffer; }
	private:
		EnumRenderParamType m_paramType;
		EnumRenderEffectDataType m_dataType;
		EnumRenderEffectParamBindType m_bindType;
		uint32 m_nStride;
		uint32 m_nArraySize;
		uint32 m_nMemorySize;

		std::string m_strName;
		size_t m_nHashName;

		HrRenderVariable* m_pRenderVariable;

		HrRenderEffectConstantBufferPtr m_pBindConstBuffer;
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

		void Dirty(bool bDirty) { m_bDirty = bDirty; };
		bool Dirty() { return m_bDirty; };

		const HrGraphicsBufferPtr& GetGraphicsBuffer() { return m_pConstantBuffer; }

		void UpdateConstantBuffer();
	private:
		HrStreamDataPtr m_pConstantBufferData;
		HrGraphicsBufferPtr m_pConstantBuffer;

		std::string m_strConstBufferName;
		size_t m_nHashName;
		size_t m_nSize;

		bool m_bDirty;
	};
}

#endif



