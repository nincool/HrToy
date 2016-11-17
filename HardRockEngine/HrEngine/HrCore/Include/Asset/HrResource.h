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
			RT_EFFECT,
			RT_SHADER,
			RT_MATERIAL,
			RT_MODEL,
		};
	public:
		HrResource() { m_bLoaded = false; };
		virtual ~HrResource() {};

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) = 0;

		std::string& GetFilePath() { return m_strFilePath; }
		std::string& GetFileName() { return m_strFileName; }
		size_t GetHashID() { return m_nHashID; }

		bool IsLoaded() { return m_bLoaded; }

		virtual bool Load()
		{
			if (m_bLoaded)
			{
				return true;
			}
			if (!LoadImpl())
			{
				return false;
			}
			m_bLoaded = true;
			return true;
		}

		virtual bool Unload()
		{
			if (!m_bLoaded)
			{
				return true;
			}
			UnloadImpl();
			m_bLoaded = false;
			return true;
		}
	protected:
		virtual bool LoadImpl() = 0;
		virtual bool UnloadImpl() = 0;
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


