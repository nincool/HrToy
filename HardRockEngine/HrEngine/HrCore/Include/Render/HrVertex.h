#ifndef _HR_Vertex_H_
#define _HR_Vertex_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrUtilTools/Include/HrUtil.h"


namespace Hr
{
	class HrVertexElement 
	{
	public:
		HrVertexElement(EnumVertexElementUsage usage, EnumVertexElementType pixelFormat)
		{
			m_elementUsage = usage;
			m_elementType = pixelFormat;
			m_nOffset = 0;
		}

		uint32 GetTypeSize() const;
		static uint32 GetTypeSize(EnumVertexElementType elementType);
		uint32 GetOffset() const { return m_nOffset; }
		void SetOffset(uint32 nOffset) { m_nOffset = nOffset; }
		
		EnumVertexElementUsage m_elementUsage;
		EnumVertexElementType m_elementType;
		uint32 m_nOffset;
	};

	class HR_CORE_API HrVertex 
	{
	public:
		HrVertex();
		~HrVertex();

	public:
		void Clear();

		void AddElementArray(std::vector<HrVertexElement>& vecVertexElement);
		void AddElementArray(HrVertexElement* pVertexElementArr, uint32 nVertexElementLength);

		uint32 GetVertexSize();
		size_t GetVertexElementNum();

		const HrVertexElement& GetVertexElement(uint32 nIndex);
	private:
		void AddElement(const HrVertexElement& usage);
	protected:
		uint32 m_nVertexSize;

		std::vector<HrVertexElement> m_vecVertexElement;
	};
}

#endif



