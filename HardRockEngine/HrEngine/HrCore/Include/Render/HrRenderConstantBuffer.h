#ifndef _HR_RENDERCONSTANTBUFFER_H_
#define _HR_RENDERCONSTANTBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderParameter.h"

namespace Hr
{
	class HR_CORE_API HrRenderConstantBuffer
	{
	public:
		HrRenderConstantBuffer();
		~HrRenderConstantBuffer();

		void SetName(std::string& name)
		{
			m_strName = name;
		}

		const std::string & GetName()
		{
			return m_strName;
		}

		void SetSize(uint64 nSize);
		uint64 GetSize();

		void AddParameter(const std::string& strName
			, HrRenderParameter::EnumRenderParamType rpt
			, HrRenderParameter::EnumRenderParamDataType rpdt
			, uint32 nStartOffset);

		IGraphicsBuffer* GetConstBuffer();

		void UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters);
	private:
		std::string m_strName;
		HrStreamData* m_pStreamData;

		IGraphicsBuffer* m_pRenderHardwareBuffer;
		std::vector<HrRenderParameter*> m_vecRenderParameter;

	};
}

#endif