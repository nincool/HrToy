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

		//������ôд��ʵ�ǲ��Ե� һ��Model�����ж��Mesh һ��Mesh�����ж��SubMesh
		HrMesh* GetMesh()
		{
			return m_pMesh;
		}

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		HrMesh* m_pMesh;
	};
}

#endif

