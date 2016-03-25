#ifndef _HR_Vertex_H_
#define _HR_Vertex_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrUtilTools/Include/HrUtil.h"


namespace Hr
{
	class HrVertexElement : public RenderSysAllocatedObject
	{
	public:
		HrVertexElement(HrVertexElement::EnumVertexElementUsage usage, EnumVertexElementType pixelFormat)
		{
			m_elementUsage = usage;
			m_elementType = pixelFormat;
			m_nOffset = 0;
		}

		size_t GetTypeSize();
		static size_t GetTypeSize(EnumVertexElementType elementType);
		HR_SYNTHESIZE(size_t, m_nOffset, Offset);
		
		EnumVertexElementUsage m_elementUsage;
		EnumVertexElementType m_elementType;
	};

	class HR_CORE_API HrVertex : public RenderSysAllocatedObject
	{
	public:
		HrVertex();
		~HrVertex();

	public:
		void Clear();
		void AddElementArray(HrVertexElement* pVertexElementArr, uint32 nVertexElementLength);

		uint32 GetVertexSize();
		size_t GetVertexElementNum();

		const HrVertexElement& GetVertexElement(uint32 nIndex);
	private:
		void AddElement(HrVertexElement& usage);
	protected:
		uint32 m_nVertexSize;

		std::vector<HrVertexElement> m_vecVertexElement;
	};
}

#endif



