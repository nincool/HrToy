#ifndef _HR_Vertex_H_
#define _HR_Vertex_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"
#include "HrUtilTools/Include/HrUtil.h"


namespace Hr
{
	class HR_CORE_API HrVertexElement
	{
	public:
		HrVertexElement(EnumVertexElementUsage usage, EnumVertexElementType pixelFormat)
		{
			m_elementUsage = usage;
			m_elementType = pixelFormat;
			m_elementClassType = VEC_GEOMETRY;
			m_nOffset = 0;
			m_nInstanceStepRate = 0;
		}

		HrVertexElement(EnumVertexElementUsage usage, EnumVertexElementType pixelFormat, EnumVertexElementClassType classType, uint32 nInsStepRate)
		{
			m_elementUsage = usage;
			m_elementType = pixelFormat;
			m_elementClassType = classType;
			m_nOffset = 0;
			m_nInstanceStepRate = nInsStepRate;
		}

		uint32 GetTypeSize() const;
		static uint32 GetTypeSize(EnumVertexElementType elementType);
		uint32 GetOffset() const { return m_nOffset; }
		void SetOffset(uint32 nOffset) { m_nOffset = nOffset; }
		
		EnumVertexElementUsage m_elementUsage;
		EnumVertexElementType m_elementType;
		EnumVertexElementClassType m_elementClassType;
		uint32 m_nOffset;
		uint32 m_nInstanceStepRate;
	};

	///////////////////////////////////////////////////////////
	//
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
	//
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
}

#endif



