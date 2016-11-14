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

		uint64 GetSize();

		void AddParameter(const std::string& strName
			, HrRenderParameter::EnumRenderParamType rpt
			, HrRenderParameter::EnumRenderParamDataType rpdt
			, uint32 nStartOffset);

		void MakeConstBuffer(uint32 nSize);

		HrGraphicsBuffer* GetConstBuffer();

		void UpdateParams(HrRenderFrameParameters& renderFrameParameters);
	private:
		std::string m_strName;
		HrStreamData* m_pStreamData;

		HrGraphicsBuffer* m_pRenderBuffer;
		std::vector<HrRenderParameter*> m_vecRenderParameter;

	};
}

#endif