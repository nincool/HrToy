#ifndef _HR_GRAPHICSBUFFER_H_
#define _HR_GRAPHICSBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"

#include <boost/noncopyable.hpp>

namespace Hr
{
	class HR_CORE_API HrGraphicsBuffer
	{
	public:
		/// Enums describing buffer usage; not mutually exclusive
		enum EnumGraphicsBufferUsage
		{
			HBU_GPUREAD_GPUWRITE,
			HBU_GPUREAD_CPUWRITE,
			HBU_GPUREAD_IMMUTABLE,
			HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};

		enum EnumGraphicsBufferBind
		{
			HBB_VERTEXT,
			HBB_INDEX,
			HBB_CONST
		};

		enum EnumGraphicsBufferAccess
		{
			HBA_READ_ONLY,
			HBA_WRITE_ONLY,
			HBA_READ_WRITE,
			HBA_WRITE_NO_OVEWRITE
		};

	public:
		class Mapper : boost::noncopyable
		{
			friend class HrGraphicsBuffer;
		public:
			Mapper(HrGraphicsBuffer& buffer, HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag)
				: buffer_(buffer)
			{
				data_ = buffer_.Map(accessFlag);
			}
			~Mapper()
			{
				buffer_.Unmap();
			}

			template <typename T>
			const T* Pointer() const
			{
				return static_cast<T*>(data_);
			}
			template <typename T>
			T* Pointer()
			{
				return static_cast<T*>(data_);
			}

		private:
			HrGraphicsBuffer& buffer_;
			void* data_;
		};
	public:
		HrGraphicsBuffer();
	
		virtual ~HrGraphicsBuffer();

		virtual void BindStream(const char* pBuffer
			, uint64 nBufferSize
			, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
			, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag);
		
		virtual uint32 GetByteWidth();

	private:
		virtual void* Map(HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag) = 0;
		virtual void Unmap() = 0;
	protected:
		uint32 m_nByteWidth;
		HrGraphicsBuffer::EnumGraphicsBufferUsage m_usage;
		HrGraphicsBuffer::EnumGraphicsBufferBind m_bindFlag;

	};
}

#endif
