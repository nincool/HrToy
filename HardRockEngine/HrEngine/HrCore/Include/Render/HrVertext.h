#ifndef _HR_VERTEXT_H_
#define _HR_VERTEXT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrCore/Include/Render/HrPixelFormat.h"
#include "HrUtilTools/Include/HrUtil.h"


namespace Hr
{
	class HrVertextElement : public RenderSysAllocatedObject
	{
	public:
		enum EnumVertextElementUsage
		{
			// vertex positions
			VEU_POSITION = 1,
			// vertex normals included (for lighting)
			VEU_NORMAL = 1 << 1,
			// Vertex colors - diffuse
			VEU_DIFFUSE = 1 << 2,
			// Vertex colors - specular
			VEU_SPECULAR = 1 << 3,
			// Vertex blend weights
			VEU_BLENDWEIGHT = 1 << 4,
			// Vertex blend indices
			VEU_BLENDINDEX = 1 << 5,
			// at least one set of texture coords (exact number specified in class)
			VEU_TEXTURECOORD = 1 << 6,
			// Vertex tangent
			VEU_TANGENT = 1 << 7,
			// Vertex binormal
			VEU_BINORMAL = 1 << 8
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

	public:
		HrVertextElement(HrVertextElement::EnumVertextElementUsage usage, EnumVertexElementType pixelFormat)
		{
			m_elementUsage = usage;
			m_elementType = pixelFormat;
			m_nOffset = 0;
		}

		size_t GetTypeSize();
		static size_t GetTypeSize(EnumVertexElementType elementType);
		HR_SYNTHESIZE(size_t, m_nOffset, Offset);
		
		EnumVertextElementUsage m_elementUsage;
		EnumVertexElementType m_elementType;
	};

	class HR_CORE_API HrVertext : public RenderSysAllocatedObject
	{
	public:
		HrVertext();
		~HrVertext();

	public:
		void Clear();
		void AddElementArray(HrVertextElement* pVertexElementArr, uint32 nVertexElementLength);

		uint32 GetVertextSize();
		size_t GetVertextElementNum();

		const HrVertextElement& GetVertextElement(uint32 nIndex);
	private:
		void AddElement(HrVertextElement& usage);
	protected:
		uint32 m_nVertexSize;

		std::vector<HrVertextElement> m_vecVertextElement;
	};
}

#endif



