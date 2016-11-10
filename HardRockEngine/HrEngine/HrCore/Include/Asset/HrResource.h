#ifndef _HR_RESOURCE_H_
#define _HR_RESOURCE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResource
	{
	public:
		enum EnumResourceType
		{
			RT_TEXTURE,
			RT_MESH,
			RT_SHADER,
			RT_MATERIAL,
			RT_MODEL,
		};
	public:
		HrResource() { m_bLoaded = false; };
		virtual ~HrResource() {};

		virtual void DeclareResource(std::string& strFilePath, std::string& strFileName) = 0;

		std::string& GetFilePath() { return m_strFilePath; }
		std::string& GetFileName() { return m_strFileName; }
		size_t GetHashID() { return m_nHashID; }

		void FinishedLoading() { m_bLoaded = true; }

		virtual void Load() = 0;
		virtual void Unload() = 0;
	protected:
		std::string m_strFilePath;
		std::string m_strFileName;

		size_t m_nHashID;

		EnumResourceType m_resType;

		//资源是否已经加载
		bool m_bLoaded;
	};
}

#endif


