#ifndef _HR_VERTEXT_H_
#define _HR_VERTEXT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrVertextElement : public RenderSysAllocatedObject
	{
	public:
		enum EnumVertextElementUsage
		{
			// vertex positions
			VEU_POSITION = 0,
			// vertex normals included (for lighting)
			VEU_NORMAL,
			// Vertex colors - diffuse
			VEU_DIFFUSE,
			// Vertex colors - specular
			VEU_SPECULAR,
			// Vertex blend weights
			VEU_BLENDWEIGHT,
			// Vertex blend indices
			VEU_BLENDINDEX,
			// at least one set of texture coords (exact number specified in class)
			VEU_TEXTURECOORD,
			// Vertex tangent
			VEU_TANGENT,
			// Vertex binormal
			VEU_BINORMAL
		};
	public:
		HrVertextElement(HrVertextElement::EnumVertextElementUsage usage)
		{
			m_vertextUsage = usage;
		}

		EnumVertextElementUsage m_vertextUsage;

	};

	class HrVertext : public RenderSysAllocatedObject
	{
	public:
		HrVertext();
		~HrVertext();

	public:
		void Clear();
		void CopyFrom(HrVertext* pVertext);
		void AddElement(HrVertextElement::EnumVertextElementUsage usage);
	protected:
		uint32 m_nVertexSize;

		std::list<HrVertextElement> m_lisVertextElement;
	};
}

#endif



