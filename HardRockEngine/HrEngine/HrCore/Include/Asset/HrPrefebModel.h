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
	protected:
		HrMesh* m_pMesh;
	};
}

#endif
