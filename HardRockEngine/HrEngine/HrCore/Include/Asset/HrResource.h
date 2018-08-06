#ifndef _HR_RESOURCE_H_
#define _HR_RESOURCE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResource : boost::noncopyable
	{
	public:
		enum EnumResourceType
		{
			RT_UNKNOWN,
			RT_MESH,
			RT_EFFECT,
			RT_MATERIAL,
			RT_MODEL,
			RT_MESHMODEL,
			RT_TEXTURE_1D,
			RT_TEXTURE_2D,
			RT_TEXTURE_3D,
			RT_TEXTURE_CUBE
		};

		enum EnumResourceStatus
		{
			RS_UNKNOWN,
			RS_DECLARED,
			RS_LOADING,
			RS_LOADED,
		};
	public:
		HrResource();
		virtual ~HrResource();

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) = 0;

		std::string& GetFilePath() { return m_strFilePath; }
		std::string& GetFileName() { return m_strFileName; }
		size_t GetHashID() { return m_nHashID; }

		bool IsDeclared() { return m_resStatus != RS_UNKNOWN; }
		bool IsLoaded() { return m_resStatus == RS_LOADED; }

		bool Load();
		bool Unload();
	protected:
		virtual bool LoadImpl() = 0;
		virtual bool UnloadImpl() = 0;
	protected:
		std::string m_strFilePath;
		std::string m_strFileName;
		std::string m_strUUID;

		size_t m_nHashID;

		EnumResourceType m_resType;
		EnumResourceStatus m_resStatus;
	};
}

#endif


