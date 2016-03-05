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
	public:
		HrVertextElement(HrVertextElement::EnumVertextElementUsage usage, PixelFormat pixelFormat)
		{
			m_vertextUsage = usage;
			m_pixelFormat = pixelFormat;
		}

		EnumVertextElementUsage m_vertextUsage;
		PixelFormat m_pixelFormat;
	};

	class HR_CORE_API HrVertext : public RenderSysAllocatedObject
	{
	public:
		HrVertext();
		~HrVertext();

	public:
		void Clear();
		void AddElementArray(HrVertextElement* pVertexElementArr, uint32 nVertexElementLength);
		void AddElement(HrVertextElement& usage);

		uint32 GetVertextSize();
	protected:
		uint32 m_nVertexSize;

		std::list<HrVertextElement> m_lisVertextElement;
	};
}

#endif



