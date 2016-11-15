#ifndef _HR_PREFEBMODEL_H_
#define _HR_PREFEBMODEL_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HrPrefebModel : public HrResource
	{
	public:
		HrPrefebModel();
		~HrPrefebModel();
	
		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		virtual void Load() override;
		virtual void Unload() override;

		//这里这么写其实是不对的 一个Model可以有多个Mesh 一个Mesh可以有多个SubMesh
		HrMesh* GetMesh()
		{
			return m_pMesh;
		}
	protected:
		HrMesh* m_pMesh;
	};
}

#endif

