#ifndef _HR_Vertex_H_
#define _HR_Vertex_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"
#include "HrUtilTools/Include/HrUtil.h"


namespace Hr
{
	enum EnumVertexElementSemantic
	{
		// vertex positions
		VEU_POSITION = 1,
		// vertex normals included (for lighting)
		VEU_NORMAL = 1 << 1,
		// Vertex -color
		VEU_COLOR = 1 << 9,
		// Vertex blend weights
		VEU_BLENDWEIGHT = 1 << 4,
		// Vertex blend indices
		VEU_BLENDINDEX = 1 << 5,
		// at least one set of texture coords (exact number specified in class)
		VEU_TEXTURE_COORDINATES = 1 << 6,
		// Vertex tangent
		VEU_TANGENT = 1 << 7,
		// Vertex binormal
		VEU_BINORMAL = 1 << 8,
	};

	/// Vertex element type, used to identify the base types of the vertex contents
	enum EnumVertexElementType
	{
		VET_FLOAT1 = 0,
		VET_FLOAT2 = 1,
		VET_FLOAT3 = 2,
		VET_FLOAT4 = 3,
		/// alias to more specific colour type - use the current rendersystem's colour packing
		VET_COLOUR = 4,
		VET_SHORT1 = 5,
		VET_SHORT2 = 6,
		VET_SHORT3 = 7,
		VET_SHORT4 = 8,
		VET_UBYTE4 = 9,
		/// D3D style compact colour
		VET_COLOUR_ARGB = 10,
		/// GL style compact colour
		VET_COLOUR_ABGR = 11,
		VET_DOUBLE1 = 12,
		VET_DOUBLE2 = 13,
		VET_DOUBLE3 = 14,
		VET_DOUBLE4 = 15,
		VET_USHORT1 = 16,
		VET_USHORT2 = 17,
		VET_USHORT3 = 18,
		VET_USHORT4 = 19,
		VET_INT1 = 20,
		VET_INT2 = 21,
		VET_INT3 = 22,
		VET_INT4 = 23,
		VET_UINT1 = 24,
		VET_UINT2 = 25,
		VET_UINT3 = 26,
		VET_UINT4 = 27
	};

	enum EnumVertexElementClassType
	{
		VEC_INSTANCE,
		VEC_GEOMETRY,
	};

	//拓扑类型
	enum EnumTopologyType
	{
		TT_POINTLIST,
		TT_LINELIST,
		TT_LINETRIP,
		TT_TRIANGLELIST,
		TT_TRIANGLETRIP,
	};

	//indice索引数据类型
	enum EnumIndexType
	{
		IT_16BIT,
		IT_32BIT,
	};

	/////////////////////////////////////////////////////
	//顶点成员描述
	/////////////////////////////////////////////////////
	class HR_CORE_API HrVertexElement
	{
	public:
		HrVertexElement(EnumVertexElementSemantic usage, EnumVertexElementType pixelFormat)
		{
			m_elementSemantic = usage;
			m_elementType = pixelFormat;
			m_elementClassType = VEC_GEOMETRY;
			m_nSemanticIndex = 0;
			m_nOffset = 0;
			m_nInstanceStepRate = 0;
		}

		HrVertexElement(EnumVertexElementSemantic usage, EnumVertexElementType pixelFormat, EnumVertexElementClassType classType, uint32 nSemanticIndex, uint32 nInsStepRate)
		{
			m_elementSemantic = usage;
			m_elementType = pixelFormat;
			m_elementClassType = classType;
			m_nSemanticIndex = nSemanticIndex;
			m_nOffset = 0;
			m_nInstanceStepRate = nInsStepRate;
		}

		uint32 GetTypeSize() const;
		static uint32 GetTypeSize(EnumVertexElementType elementType);
		uint32 GetOffset() const { return m_nOffset; }
		void SetOffset(uint32 nOffset) { m_nOffset = nOffset; }
		
		EnumVertexElementSemantic m_elementSemantic;
		EnumVertexElementType m_elementType;
		EnumVertexElementClassType m_elementClassType;
		uint32 m_nSemanticIndex;
		uint32 m_nOffset;
		uint32 m_nInstanceStepRate;

	};

	///////////////////////////////////////////////////////////
	//顶点数据的描述
	///////////////////////////////////////////////////////////

	class HR_CORE_API HrVertex 
	{
	public:
		HrVertex();
		~HrVertex();

	public:
		void Clear();

		void AddElementArray(const std::vector<HrVertexElement>& vecVertexElement);
		void AddElementArray(HrVertexElement* pVertexElementArr, uint32 nVertexElementLength);

		uint32 GetVertexSize();
		size_t GetVertexElementNum();

		const HrVertexElement& GetVertexElement(uint32 nIndex);
		const std::vector<HrVertexElement>& GetVertexElement();
	private:
		void AddElement(const HrVertexElement& usage);
	protected:
		uint32 m_nVertexSize;

		std::vector<HrVertexElement> m_vecVertexElement;
	};

	///////////////////////////////////////////////////////////
	//顶点数据
	///////////////////////////////////////////////////////////

	class HR_CORE_API HrVertexData
	{
	public:
		HrVertexData();
		~HrVertexData();

		void BindVertexStream(const char* pBuffer, uint64 nBufferSize, HrGraphicsBuffer::EnumGraphicsBufferUsage usage, uint32 nStart, uint32 nSize);

		uint32 GetVertexStart();
		uint32 GetVertexCount();

		const HrVertexPtr& GetVertex();
		const HrGraphicsBufferPtr& GetVertexStream();

		const HrStreamDataPtr& GetVertexBaseData();
	private:
		HrGraphicsBufferPtr m_pVertexStream;
		HrStreamDataPtr m_pVertexBaseData;
		HrVertexPtr m_pVertex;
		
		uint32 m_nVertexStart;
		uint32 m_nVertexCount;
	};

	///////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////

	class HR_CORE_API HrIndexData
	{
	public:
		HrIndexData();
		~HrIndexData();

		void BindIndexStream(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, uint32 nIndexCount
			, uint32 nStart = 0
			, uint32 nBaseVertex = 0);

		uint32 GetIndexStart();
		uint32 GetIndexCount();
		const HrGraphicsBufferPtr& GetIndexStream();

		EnumIndexType GetIndexBufferType();
	private:
		EnumIndexType m_indexBufferType;

		HrGraphicsBufferPtr m_pIndexStream;
		HrStreamDataPtr m_pIndexBaseData;

		uint32 m_nIndexCount;
		uint32 m_nIndexStartLocation;
		uint32 m_nBaseVertexLocation;
	};
}

#endif



